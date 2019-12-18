#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {scalar_t__ scratch; } ;
struct TYPE_7__ {int status; int /*<<< orphan*/  error; int /*<<< orphan*/  pre_parsed; scalar_t__ paused; int /*<<< orphan*/  settings; TYPE_2__* req; } ;
typedef  TYPE_1__ parser_data_t ;
struct TYPE_8__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
struct TYPE_9__ {int /*<<< orphan*/  http_errno; scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  HTTPD_400_BAD_REQUEST ; 
 int /*<<< orphan*/  HTTPD_414_URI_TOO_LONG ; 
 int /*<<< orphan*/  HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE ; 
 int /*<<< orphan*/  HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 void* PARSING_FAILED ; 
#define  PARSING_HDR_FIELD 130 
#define  PARSING_HDR_VALUE 129 
#define  PARSING_URL 128 
 int /*<<< orphan*/  TAG ; 
 size_t continue_parsing (TYPE_3__*,size_t) ; 
 size_t http_parser_execute (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,size_t) ; 

__attribute__((used)) static int parse_block(http_parser *parser, size_t offset, size_t length)
{
    parser_data_t        *data  = (parser_data_t *)(parser->data);
    httpd_req_t          *req   = data->req;
    struct httpd_req_aux *raux  = req->aux;
    size_t nparsed = 0;

    if (!length) {
        /* Parsing is still happening but nothing to
         * parse means no more space left on buffer,
         * therefore it can be inferred that the
         * request URI/header must be too long */
        ESP_LOGW(TAG, LOG_FMT("request URI/header too long"));
        switch (data->status) {
            case PARSING_URL:
                data->error = HTTPD_414_URI_TOO_LONG;
                break;
            case PARSING_HDR_FIELD:
            case PARSING_HDR_VALUE:
                data->error = HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE;
                break;
            default:
                ESP_LOGE(TAG, LOG_FMT("unexpected state"));
                data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
                break;
        }
        data->status = PARSING_FAILED;
        return -1;
    }

    /* Un-pause the parsing if paused */
    if (data->paused) {
        nparsed = continue_parsing(parser, length);
        length -= nparsed;
        offset += nparsed;
        if (!length) {
            return nparsed;
        }
    }

    /* Execute http_parser */
    nparsed = http_parser_execute(parser, &data->settings,
                                  raux->scratch + offset, length);

    /* Check state */
    if (data->status == PARSING_FAILED) {
        /* It is expected that the error field of
         * parser data should have been set by now */
        ESP_LOGW(TAG, LOG_FMT("parsing failed"));
        return -1;
    } else if (data->paused) {
        /* Update the value of pre_parsed which was set when
         * pause_parsing() was called. (length - nparsed) is
         * the length of the data that will need to be parsed
         * again later and hence must be deducted from the
         * pre_parsed length */
        data->pre_parsed -= (length - nparsed);
        return 0;
    } else if (nparsed != length) {
        /* http_parser error */
        data->error  = HTTPD_400_BAD_REQUEST;
        data->status = PARSING_FAILED;
        ESP_LOGW(TAG, LOG_FMT("incomplete (%d/%d) with parser error = %d"),
                 nparsed, length, parser->http_errno);
        return -1;
    }

    /* Return with the total length of the request packet
     * that has been parsed till now */
    ESP_LOGD(TAG, LOG_FMT("parsed block size = %d"), offset + nparsed);
    return offset + nparsed;
}