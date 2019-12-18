#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct httpd_req_aux {struct httpd_data* resp_hdrs; } ;
struct httpd_data {struct httpd_data* hd_calls; struct httpd_data* hd_sd; struct httpd_data* err_handler_fns; struct httpd_req_aux hd_req_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_unregister_all_uri_handlers (struct httpd_data*) ; 

__attribute__((used)) static void httpd_delete(struct httpd_data *hd)
{
    struct httpd_req_aux *ra = &hd->hd_req_aux;
    /* Free memory of httpd instance data */
    free(hd->err_handler_fns);
    free(ra->resp_hdrs);
    free(hd->hd_sd);

    /* Free registered URI handlers */
    httpd_unregister_all_uri_handlers(hd);
    free(hd->hd_calls);
    free(hd);
}