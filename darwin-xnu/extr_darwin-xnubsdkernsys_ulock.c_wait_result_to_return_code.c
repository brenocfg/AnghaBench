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
typedef  int wait_result_t ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
#define  THREAD_AWAKENED 131 
#define  THREAD_INTERRUPTED 130 
#define  THREAD_RESTART 129 
#define  THREAD_TIMED_OUT 128 

__attribute__((used)) inline static int
wait_result_to_return_code(wait_result_t wr)
{
	int ret = 0;

	switch (wr) {
	case THREAD_AWAKENED:
		break;
	case THREAD_TIMED_OUT:
		ret = ETIMEDOUT;
		break;
	case THREAD_INTERRUPTED:
	case THREAD_RESTART:
	default:
		ret = EINTR;
		break;
	}

	return ret;
}