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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int ref_count; int /*<<< orphan*/  udata_free; int /*<<< orphan*/  udata; } ;
typedef  TYPE_1__ GRef ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  g_return_if_fail (int) ; 

void g_ref_set(GRef *ref, gpointer udata, GDestroyNotify udata_free) {
	g_return_if_fail(ref->ref_count == 0);
	
	ref->udata = udata;
	ref->udata_free = udata_free;
	ref->ref_count = 1;
}