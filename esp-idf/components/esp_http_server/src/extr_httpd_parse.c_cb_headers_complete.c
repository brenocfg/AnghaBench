#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {char* scratch; scalar_t__ remaining_len; int /*<<< orphan*/  req_hdrs_count; } ;
struct httpd_req {scalar_t__ content_len; struct httpd_req_aux* aux; } ;
typedef  int ssize_t ;
struct TYPE_6__ {char* at; int length; } ;
struct TYPE_7__ {scalar_t__ status; int raw_datalen; void* error; TYPE_1__ last; struct httpd_req* req; } ;
typedef  TYPE_2__ parser_data_t ;
struct TYPE_8__ {scalar_t__ upgrade; scalar_t__ nread; scalar_t__ content_length; scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 void* HTTPD_400_BAD_REQUEST ; 
 void* HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 scalar_t__ PARSING_BODY ; 
 void* PARSING_FAILED ; 
 scalar_t__ PARSING_HDR_VALUE ; 
 scalar_t__ PARSING_URL ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ verify_url (TYPE_3__*) ; 

__attribute__((used)) static esp_err_t cb_headers_complete(http_parser *parser)
{
    parser_data_t *parser_data = (parser_data_t *) parser->data;
    struct httpd_req *r        = parser_data->req;
    struct httpd_req_aux *ra   = r->aux;

    /* Check previous status */
    if (parser_data->status == PARSING_URL) {
        ESP_LOGD(TAG, LOG_FMT("no headers"));
        if (verify_url(parser) != ESP_OK) {
            /* verify_url would already have set the
             * error field of parser data, so only setting
             * status to failed */
            parser_data->status = PARSING_FAILED;
            return ESP_FAIL;
        }
    } else if (parser_data->status == PARSING_HDR_VALUE) {
        /* Locate end of last header */
        char *at = (char *)parser_data->last.at + parser_data->last.length;

        /* Check if there is data left to parse. This value should
         * at least be equal to the number of line terminators, i.e. 2 */
        ssize_t remaining_length = parser_data->raw_datalen - (at - ra->scratch);
        if (remaining_length < 2) {
            ESP_LOGE(TAG, LOG_FMT("invalid length of data remaining to be parsed"));
            parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
            parser_data->status = PARSING_FAILED;
            return ESP_FAIL;
        }

        /* Locate end of headers section by skipping the remaining
         * two line terminators. No assumption is made here about the
         * termination sequence used apart from the necessity that it
         * must end with an LF, because:
         *      1) some clients may send non standard LFs instead of
         *         CRLFs for indicating termination.
         *      2) it is the responsibility of http_parser to check
         *         that the termination is either CRLF or LF and
         *         not any other sequence */
        unsigned short remaining_terminators = 2;
        while (remaining_length-- && remaining_terminators) {
            if (*at == '\n') {
                remaining_terminators--;
            }
            /* Overwrite termination characters with null */
            *(at++) = '\0';
        }
        if (remaining_terminators) {
            ESP_LOGE(TAG, LOG_FMT("incomplete termination of headers"));
            parser_data->error = HTTPD_400_BAD_REQUEST;
            parser_data->status = PARSING_FAILED;
            return ESP_FAIL;
        }

        /* Place the parser ptr right after the end of headers section */
        parser_data->last.at = at;

        /* Increment header count */
        ra->req_hdrs_count++;
    } else {
        ESP_LOGE(TAG, LOG_FMT("unexpected state transition"));
        parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    /* In absence of body/chunked encoding, http_parser sets content_len to -1 */
    r->content_len = ((int)parser->content_length != -1 ?
                      parser->content_length : 0);

    ESP_LOGD(TAG, LOG_FMT("bytes read     = %d"),  parser->nread);
    ESP_LOGD(TAG, LOG_FMT("content length = %zu"), r->content_len);

    if (parser->upgrade) {
        ESP_LOGW(TAG, LOG_FMT("upgrade from HTTP not supported"));
        /* There is no specific HTTP error code to notify the client that
         * upgrade is not supported, thus sending 400 Bad Request */
        parser_data->error = HTTPD_400_BAD_REQUEST;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    parser_data->status = PARSING_BODY;
    ra->remaining_len = r->content_len;
    return ESP_OK;
}