#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct async_resp_arg {scalar_t__ fd; int /*<<< orphan*/  hd; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STR ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  generate_async_resp ; 
 int /*<<< orphan*/  httpd_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct async_resp_arg*) ; 
 scalar_t__ httpd_req_to_sockfd (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_resp_send (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct async_resp_arg* malloc (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t async_get_handler(httpd_req_t *req)
{
#define STR "Hello World!"
    httpd_resp_send(req, STR, strlen(STR));
    /* Also register a HTTPD Work which sends the same data on the same
     * socket again
     */
    struct async_resp_arg *resp_arg = malloc(sizeof(struct async_resp_arg));
    resp_arg->hd = req->handle;
    resp_arg->fd = httpd_req_to_sockfd(req);
    if (resp_arg->fd < 0) {
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Queuing work fd : %d", resp_arg->fd);
    httpd_queue_work(req->handle, generate_async_resp, resp_arg);
    return ESP_OK;
#undef STR
}