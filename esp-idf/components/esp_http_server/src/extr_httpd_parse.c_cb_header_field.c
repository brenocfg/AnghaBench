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
struct httpd_req_aux {char const* scratch; int /*<<< orphan*/  req_hdrs_count; } ;
struct httpd_req {struct httpd_req_aux* aux; } ;
struct TYPE_7__ {char const* at; int length; } ;
struct TYPE_8__ {scalar_t__ status; TYPE_1__ last; void* error; struct httpd_req* req; } ;
typedef  TYPE_2__ parser_data_t ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 void* HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 void* PARSING_FAILED ; 
 scalar_t__ PARSING_HDR_FIELD ; 
 scalar_t__ PARSING_HDR_VALUE ; 
 scalar_t__ PARSING_URL ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ pause_parsing (TYPE_3__*,char const*) ; 
 scalar_t__ verify_url (TYPE_3__*) ; 

__attribute__((used)) static esp_err_t cb_header_field(http_parser *parser, const char *at, size_t length)
{
    parser_data_t *parser_data = (parser_data_t *) parser->data;
    struct httpd_req *r        = parser_data->req;
    struct httpd_req_aux *ra   = r->aux;

    /* Check previous status */
    if (parser_data->status == PARSING_URL) {
        if (verify_url(parser) != ESP_OK) {
            /* verify_url would already have set the
             * error field of parser data, so only setting
             * status to failed */
            parser_data->status = PARSING_FAILED;
            return ESP_FAIL;
        }

        ESP_LOGD(TAG, LOG_FMT("headers begin"));
        /* Last at is set to start of scratch where headers
         * will be received next */
        parser_data->last.at     = ra->scratch;
        parser_data->last.length = 0;
        parser_data->status      = PARSING_HDR_FIELD;

        /* Stop parsing for now and give control to process */
        if (pause_parsing(parser, at) != ESP_OK) {
            parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
            parser_data->status = PARSING_FAILED;
            return ESP_FAIL;
        }
    } else if (parser_data->status == PARSING_HDR_VALUE) {
        /* Overwrite terminator (CRLFs) following last header
         * (key: value) pair with null characters */
        char *term_start = (char *)parser_data->last.at + parser_data->last.length;
        memset(term_start, '\0', at - term_start);

        /* Store current values of the parser callback arguments */
        parser_data->last.at     = at;
        parser_data->last.length = 0;
        parser_data->status      = PARSING_HDR_FIELD;

        /* Increment header count */
        ra->req_hdrs_count++;
    } else if (parser_data->status != PARSING_HDR_FIELD) {
        ESP_LOGE(TAG, LOG_FMT("unexpected state transition"));
        parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, LOG_FMT("processing field = %.*s"), length, at);

    /* Update length of header string */
    parser_data->last.length += length;
    return ESP_OK;
}