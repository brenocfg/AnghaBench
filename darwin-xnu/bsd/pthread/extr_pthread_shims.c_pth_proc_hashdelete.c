#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pth_proc_hashdelete ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
pth_proc_hashdelete(proc_t p)
{
	pthread_functions->pth_proc_hashdelete(p);
}