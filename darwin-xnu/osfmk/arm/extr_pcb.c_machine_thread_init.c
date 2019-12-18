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
typedef  int /*<<< orphan*/  arm_debug_state_t ;

/* Variables and functions */
 int THREAD_CHUNK ; 
 int /*<<< orphan*/  ads_zone ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 

void
machine_thread_init(void)
{
	ads_zone = zinit(sizeof(arm_debug_state_t),
					 THREAD_CHUNK * (sizeof(arm_debug_state_t)),
					 THREAD_CHUNK * (sizeof(arm_debug_state_t)),
					 "arm debug state");
}