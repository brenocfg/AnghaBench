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
struct TYPE_6__ {scalar_t__ length; scalar_t__ at; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_1__ last; void* error; } ;
typedef  TYPE_2__ parser_data_t ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 void* HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 scalar_t__ PARSING_BODY ; 
 scalar_t__ PARSING_COMPLETE ; 
 void* PARSING_FAILED ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ pause_parsing (TYPE_3__*,char const*) ; 

__attribute__((used)) static esp_err_t cb_on_body(http_parser *parser, const char *at, size_t length)
{
    parser_data_t *parser_data = (parser_data_t *) parser->data;

    /* Check previous status */
    if (parser_data->status != PARSING_BODY) {
        ESP_LOGE(TAG, LOG_FMT("unexpected state transition"));
        parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    /* Pause parsing so that if part of another packet
     * is in queue then it doesn't get parsed, which
     * may reset the parser state and cause current
     * request packet to be lost */
    if (pause_parsing(parser, at) != ESP_OK) {
        parser_data->error = HTTPD_500_INTERNAL_SERVER_ERROR;
        parser_data->status = PARSING_FAILED;
        return ESP_FAIL;
    }

    parser_data->last.at     = 0;
    parser_data->last.length = 0;
    parser_data->status      = PARSING_COMPLETE;
    ESP_LOGD(TAG, LOG_FMT("body begins"));
    return ESP_OK;
}