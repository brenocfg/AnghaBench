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
struct sock_db {int /*<<< orphan*/  ignore_sess_ctx_changes; int /*<<< orphan*/  free_ctx; int /*<<< orphan*/  ctx; } ;
struct httpd_req_aux {char* status; char* content_type; int first_chunk_sent; struct sock_db* sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ignore_sess_ctx_changes; int /*<<< orphan*/  free_ctx; int /*<<< orphan*/  sess_ctx; struct httpd_req_aux* aux; struct httpd_data* handle; } ;
struct httpd_data {struct httpd_req_aux hd_req_aux; int /*<<< orphan*/  config; TYPE_1__ hd_req; } ;
typedef  TYPE_1__ httpd_req_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ HTTPD_200 ; 
 scalar_t__ HTTPD_TYPE_TEXT ; 
 scalar_t__ httpd_parse_req (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_req_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  init_req (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_req_aux (struct httpd_req_aux*,int /*<<< orphan*/ *) ; 

esp_err_t httpd_req_new(struct httpd_data *hd, struct sock_db *sd)
{
    httpd_req_t *r = &hd->hd_req;
    init_req(r, &hd->config);
    init_req_aux(&hd->hd_req_aux, &hd->config);
    r->handle = hd;
    r->aux = &hd->hd_req_aux;
    /* Associate the request to the socket */
    struct httpd_req_aux *ra = r->aux;
    ra->sd = sd;
    /* Set defaults */
    ra->status = (char *)HTTPD_200;
    ra->content_type = (char *)HTTPD_TYPE_TEXT;
    ra->first_chunk_sent = false;
    /* Copy session info to the request */
    r->sess_ctx = sd->ctx;
    r->free_ctx = sd->free_ctx;
    r->ignore_sess_ctx_changes = sd->ignore_sess_ctx_changes;
    /* Parse request */
    esp_err_t err = httpd_parse_req(hd);
    if (err != ESP_OK) {
        httpd_req_cleanup(r);
    }
    return err;
}