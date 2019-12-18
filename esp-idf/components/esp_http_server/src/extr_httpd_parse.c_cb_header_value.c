#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* at; scalar_t__ length; } ;
struct TYPE_6__ {scalar_t__ status; TYPE_1__ last; int /*<<< orphan*/  error; } ;
typedef  TYPE_2__ parser_data_t ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char const*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 scalar_t__ PARSING_FAILED ; 
 scalar_t__ PARSING_HDR_FIELD ; 
 scalar_t__ PARSING_HDR_VALUE ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static esp_err_t cb_header_value(http_parser *parser, const char *at, size_t length)
{
    parser_data_t *parser_data = (parser_data_t *) parser->data;

    /* Check previous status */
    if (parser_data->status == PARSING_HDR_FIELD) {
        /* Store current values of the parser callback arguments */
        parser_data->last.at     = at;
        parser_data->last.length = 0;
        parser_data->status      = PARSING_HDR_VALUE;

        if (length == 0) {
            /* As per behavior of http_parser, when length > 0,
             * `at` points to the start of CRLF. But, in the
             * case when header value is empty (zero length),
             * then `at` points to the position right after
             * the CRLF. Since for our purpose we need `last.at`
             * to point to exactly where the CRLF starts, it
             * needs to be adjusted by the right offset */
            char *at_adj = (char *)parser_data->last.at;
            /* Find the end of header field string */
            while (*(--at_adj) != ':');
            /* Now skip leading spaces' */
            while (*(++at_adj) == ' ');
            /* Now we are at the right position */
            parser_data->last.at = at_adj;
        }
    } else if (parser_data->status != PARSING_HDR_VALUE) {
        ESP_LOGE(TAG, LOG_FMT("unexpected state transition"));
        parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, LOG_FMT("processing value = %.*s"), length, at);

    /* Update length of header string */
    parser_data->last.length += length;
    return ESP_OK;
}