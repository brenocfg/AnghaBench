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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  in_val ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_threadid_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
turnstile_prim_unlock(int type)
{
	int ret;
	uint64_t tid;
	int in_val = type;
	pthread_threadid_np(NULL, &tid);
	T_LOG("sysctlbyname unlock called from thread %llu \n", tid);
	ret = sysctlbyname("kern.turnstiles_test_unlock", NULL, 0, &in_val, sizeof(in_val));
	T_LOG("sysctlbyname unlock returned from thread %llu with value %d \n", tid, ret);
}