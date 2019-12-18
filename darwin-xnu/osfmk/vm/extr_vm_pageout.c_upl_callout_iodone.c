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
typedef  TYPE_1__* upl_t ;
struct upl_io_completion {void (* io_done ) (void*,int) ;void* io_context; int io_error; } ;
struct TYPE_3__ {struct upl_io_completion* upl_iodone; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void (*) (void*,int)) ; 
 void stub1 (void*,int) ; 

void upl_callout_iodone(upl_t upl)
{
        struct upl_io_completion *upl_ctx = upl->upl_iodone;

	if (upl_ctx) {
	        void    (*iodone_func)(void *, int) = upl_ctx->io_done;

		assert(upl_ctx->io_done);

		(*iodone_func)(upl_ctx->io_context, upl_ctx->io_error);
	}
}