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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  mutex_t ;
typedef  int /*<<< orphan*/  cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LWP_THREADQ_NOTIMEOUT ; 
 int /*<<< orphan*/  __lwp_cond_waitsupp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 LWP_CondWait(cond_t cond,mutex_t mutex)
{
	return __lwp_cond_waitsupp(cond,mutex,LWP_THREADQ_NOTIMEOUT,FALSE);
}