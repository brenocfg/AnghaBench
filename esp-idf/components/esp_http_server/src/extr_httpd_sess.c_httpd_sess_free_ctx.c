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
typedef  int /*<<< orphan*/  (* httpd_free_ctx_fn_t ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

void httpd_sess_free_ctx(void *ctx, httpd_free_ctx_fn_t free_fn)
{
    if (ctx) {
        if (free_fn) {
            free_fn(ctx);
        } else {
            free(ctx);
        }
    }
}