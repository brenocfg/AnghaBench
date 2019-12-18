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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  MsGetHiResCounter () ; 
 float MsGetHiResTimeSpan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 

UINT64 TickHighres64()
{

#ifdef	OS_WIN32

	return (UINT64)(MsGetHiResTimeSpan(MsGetHiResCounter()) * 1000.0f);

#else	// OS_WIN32

	return Tick64();

#endif	// OS_WIN32

}