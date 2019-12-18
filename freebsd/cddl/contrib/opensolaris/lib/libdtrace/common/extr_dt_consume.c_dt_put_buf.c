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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {struct TYPE_4__* dtbd_data; } ;
typedef  TYPE_1__ dtrace_bufdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
dt_put_buf(dtrace_hdl_t *dtp, dtrace_bufdesc_t *buf)
{
	dt_free(dtp, buf->dtbd_data);
	dt_free(dtp, buf);
}