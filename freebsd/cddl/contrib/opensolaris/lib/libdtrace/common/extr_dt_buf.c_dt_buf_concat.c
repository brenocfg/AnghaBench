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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {scalar_t__ dbu_err; scalar_t__ dbu_buf; scalar_t__ dbu_ptr; } ;
typedef  TYPE_1__ dt_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_buf_write (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,size_t,size_t) ; 
 int /*<<< orphan*/  dt_set_errno (int /*<<< orphan*/ *,scalar_t__) ; 

void
dt_buf_concat(dtrace_hdl_t *dtp, dt_buf_t *dst,
    const dt_buf_t *src, size_t align)
{
	if (dst->dbu_err == 0 && src->dbu_err != 0) {
		(void) dt_set_errno(dtp, src->dbu_err);
		dst->dbu_err = src->dbu_err;
	} else {
		dt_buf_write(dtp, dst, src->dbu_buf,
		    (size_t)(src->dbu_ptr - src->dbu_buf), align);
	}
}