#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct httpd_data {int /*<<< orphan*/  hd_req; } ;
struct TYPE_3__ {scalar_t__ status; int raw_datalen; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ parser_data_t ;
typedef  int /*<<< orphan*/  httpd_req_t ;
typedef  int /*<<< orphan*/  http_parser ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HTTPD_SOCK_ERR_TIMEOUT ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  PARSER_BLOCK_SIZE ; 
 scalar_t__ PARSING_COMPLETE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  httpd_req_handle_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_uri (struct httpd_data*) ; 
 int parse_block (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  parse_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int read_block (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t httpd_parse_req(struct httpd_data *hd)
{
    httpd_req_t *r = &hd->hd_req;
    int blk_len,  offset;
    http_parser   parser;
    parser_data_t parser_data;

    /* Initialize parser */
    parse_init(r, &parser, &parser_data);

    /* Set offset to start of scratch buffer */
    offset = 0;
    do {
        /* Read block into scratch buffer */
        if ((blk_len = read_block(r, offset, PARSER_BLOCK_SIZE)) < 0) {
            if (blk_len == HTTPD_SOCK_ERR_TIMEOUT) {
                /* Retry read in case of non-fatal timeout error.
                 * read_block() ensures that the timeout error is
                 * handled properly so that this doesn't get stuck
                 * in an infinite loop */
                continue;
            }
            /* If not HTTPD_SOCK_ERR_TIMEOUT, returned error must
             * be HTTPD_SOCK_ERR_FAIL which means we need to return
             * failure and thereby close the underlying socket */
            return ESP_FAIL;
        }

        /* This is used by the callbacks to track
         * data usage of the buffer */
        parser_data.raw_datalen = blk_len + offset;

        /* Parse data block from buffer */
        if ((offset = parse_block(&parser, offset, blk_len)) < 0) {
            /* HTTP error occurred.
             * Send error code as response status and
             * invoke error handler */
            return httpd_req_handle_err(r, parser_data.error);
        }
    } while (parser_data.status != PARSING_COMPLETE);

    ESP_LOGD(TAG, LOG_FMT("parsing complete"));
    return httpd_uri(hd);
}