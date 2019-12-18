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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/ * __dvd_waitingqueue ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dvd_clearwaitingqueue()
{
	u32 i;

	for(i=0;i<4;i++)
		__lwp_queue_init_empty(&__dvd_waitingqueue[i]);
}