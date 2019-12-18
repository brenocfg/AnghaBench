#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
struct TYPE_5__ {int ignore_sess_ctx_changes; scalar_t__ sess_ctx; struct httpd_req_aux* aux; int /*<<< orphan*/ * handle; int /*<<< orphan*/  free_ctx; } ;
typedef  TYPE_2__ httpd_req_t ;
struct TYPE_4__ {scalar_t__ ctx; int ignore_sess_ctx_changes; int /*<<< orphan*/  free_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  httpd_sess_free_ctx (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void httpd_req_cleanup(httpd_req_t *r)
{
    struct httpd_req_aux *ra = r->aux;

    /* Check if the context has changed and needs to be cleared */
    if ((r->ignore_sess_ctx_changes == false) && (ra->sd->ctx != r->sess_ctx)) {
        httpd_sess_free_ctx(ra->sd->ctx, ra->sd->free_ctx);
    }
    /* Retrieve session info from the request into the socket database. */
    ra->sd->ctx = r->sess_ctx;
    ra->sd->free_ctx = r->free_ctx;
    ra->sd->ignore_sess_ctx_changes = r->ignore_sess_ctx_changes;

    /* Clear out the request and request_aux structures */
    ra->sd = NULL;
    r->handle = NULL;
    r->aux = NULL;
}