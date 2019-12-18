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
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTC_STATE_STOPPED ; 
 int /*<<< orphan*/  ctcm_chx_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void ctcm_chx_stopped(fsm_instance *fi, int event, void *arg)
{
	ctcm_chx_cleanup(fi, CTC_STATE_STOPPED, arg);
}