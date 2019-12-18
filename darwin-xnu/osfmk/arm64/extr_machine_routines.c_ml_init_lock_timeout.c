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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  slto ;
typedef  int /*<<< orphan*/  mtxspin ;

/* Variables and functions */
 int LockTimeOut ; 
 int LockTimeOutUsec ; 
 int MutexSpin ; 
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 scalar_t__ PE_parse_boot_argn (char*,int*,int) ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int*) ; 

void
ml_init_lock_timeout(void)
{
	uint64_t        abstime;
	uint64_t        mtxspin;
	uint64_t        default_timeout_ns = NSEC_PER_SEC>>2;
	uint32_t        slto;

	if (PE_parse_boot_argn("slto_us", &slto, sizeof (slto)))
		default_timeout_ns = slto * NSEC_PER_USEC;

	nanoseconds_to_absolutetime(default_timeout_ns, &abstime);
	LockTimeOutUsec = (uint32_t)(abstime / NSEC_PER_USEC);
	LockTimeOut = (uint32_t)abstime;

	if (PE_parse_boot_argn("mtxspin", &mtxspin, sizeof (mtxspin))) {
		if (mtxspin > USEC_PER_SEC>>4)
			mtxspin =  USEC_PER_SEC>>4;
			nanoseconds_to_absolutetime(mtxspin*NSEC_PER_USEC, &abstime);
	} else {
		nanoseconds_to_absolutetime(10*NSEC_PER_USEC, &abstime);
	}
	MutexSpin = abstime;
}