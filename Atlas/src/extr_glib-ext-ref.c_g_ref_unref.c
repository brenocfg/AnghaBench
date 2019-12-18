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
struct TYPE_4__ {scalar_t__ ref_count; int /*<<< orphan*/ * udata; int /*<<< orphan*/  (* udata_free ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ GRef ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void g_ref_unref(GRef *ref) {
	if (ref->ref_count == 0) {
		/* not set yet */
	} else if (--ref->ref_count == 0) {
		if (ref->udata_free) {
			ref->udata_free(ref->udata);
			ref->udata = NULL;
		}
		g_free(ref);
	}
}