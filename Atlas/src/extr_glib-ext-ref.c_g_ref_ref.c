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
struct TYPE_3__ {scalar_t__ ref_count; } ;
typedef  TYPE_1__ GRef ;

/* Variables and functions */
 int /*<<< orphan*/  g_return_if_fail (int) ; 

void g_ref_ref(GRef *ref) {
	g_return_if_fail(ref->ref_count > 0);
	
	ref->ref_count++;
}