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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  kMemorystatusKilledFCThrashing 130 
#define  kMemorystatusKilledVMCompressorSpaceShortage 129 
#define  kMemorystatusKilledVMCompressorThrashing 128 

__attribute__((used)) static boolean_t
is_reason_thrashing(unsigned cause)
{
	switch (cause) {
	case kMemorystatusKilledFCThrashing:
	case kMemorystatusKilledVMCompressorThrashing:
	case kMemorystatusKilledVMCompressorSpaceShortage:
		return TRUE;
	default:
		return FALSE;
	}
}