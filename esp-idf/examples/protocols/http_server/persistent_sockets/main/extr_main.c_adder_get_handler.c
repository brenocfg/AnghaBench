#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  outbuf ;
struct TYPE_4__ {scalar_t__ sess_ctx; int /*<<< orphan*/  free_ctx; scalar_t__ user_ctx; } ;
typedef  TYPE_1__ httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  adder_free_func ; 
 int /*<<< orphan*/  httpd_resp_send (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static esp_err_t adder_get_handler(httpd_req_t *req)
{
    /* Log total visitors */
    unsigned *visitors = (unsigned *)req->user_ctx;
    ESP_LOGI(TAG, "/adder visitor count = %d", ++(*visitors));

    char outbuf[50];

    /* Create session's context if not already available */
    if (! req->sess_ctx) {
        ESP_LOGI(TAG, "/adder GET allocating new session");
        req->sess_ctx = malloc(sizeof(int));
        req->free_ctx = adder_free_func;
        *(int *)req->sess_ctx = 0;
    }
    ESP_LOGI(TAG, "/adder GET handler send %d", *(int *)req->sess_ctx);

    /* Respond with the accumulated value */
    snprintf(outbuf, sizeof(outbuf),"%d", *((int *)req->sess_ctx));
    httpd_resp_send(req, outbuf, strlen(outbuf));
    return ESP_OK;
}