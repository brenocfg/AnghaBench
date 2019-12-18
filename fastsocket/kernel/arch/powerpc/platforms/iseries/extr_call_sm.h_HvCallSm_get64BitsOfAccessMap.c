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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  HvLpIndex ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallSmGet64BitsOfAccessMap ; 

__attribute__((used)) static inline u64 HvCallSm_get64BitsOfAccessMap(HvLpIndex lpIndex,
		u64 indexIntoBitMap)
{
	return HvCall2(HvCallSmGet64BitsOfAccessMap, lpIndex, indexIntoBitMap);
}