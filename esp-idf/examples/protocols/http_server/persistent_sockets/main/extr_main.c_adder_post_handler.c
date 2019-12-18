#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  outbuf ;
struct TYPE_6__ {scalar_t__ sess_ctx; int /*<<< orphan*/  free_ctx; scalar_t__ user_ctx; } ;
typedef  TYPE_1__ httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int HTTPD_SOCK_ERR_TIMEOUT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  adder_free_func ; 
 int atoi (char*) ; 
 int httpd_req_recv (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  httpd_resp_send (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_resp_send_408 (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static esp_err_t adder_post_handler(httpd_req_t *req)
{
    /* Log total visitors */
    unsigned *visitors = (unsigned *)req->user_ctx;
    ESP_LOGI(TAG, "/adder visitor count = %d", ++(*visitors));

    char buf[10];
    char outbuf[50];
    int  ret;

    /* Read data received in the request */
    ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    buf[ret] = '\0';
    int val = atoi(buf);
    ESP_LOGI(TAG, "/adder handler read %d", val);

    /* Create session's context if not already available */
    if (! req->sess_ctx) {
        ESP_LOGI(TAG, "/adder allocating new session");
        req->sess_ctx = malloc(sizeof(int));
        req->free_ctx = adder_free_func;
        *(int *)req->sess_ctx = 0;
    }

    /* Add the received data to the context */
    int *adder = (int *)req->sess_ctx;
    *adder += val;

    /* Respond with the accumulated value */
    snprintf(outbuf, sizeof(outbuf),"%d", *adder);
    httpd_resp_send(req, outbuf, strlen(outbuf));
    return ESP_OK;
}