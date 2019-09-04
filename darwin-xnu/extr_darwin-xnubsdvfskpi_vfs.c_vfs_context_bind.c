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
typedef  TYPE_1__* vfs_context_t ;
struct TYPE_3__ {int /*<<< orphan*/  vc_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 

int
vfs_context_bind(vfs_context_t ctx)
{
	ctx->vc_thread = current_thread();
	return 0;
}