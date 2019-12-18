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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCall4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HvCallHptInvalidateNoSyncICache ; 
 int /*<<< orphan*/  HvCallHptInvalidateSetSwBitsGet ; 

__attribute__((used)) static inline u64 HvCallHpt_invalidateSetSwBitsGet(u32 hpteIndex, u8 bitson,
		u8 bitsoff)
{
	u64 compressedStatus;

	compressedStatus = HvCall4(HvCallHptInvalidateSetSwBitsGet,
			hpteIndex, bitson, bitsoff, 1);
	HvCall1(HvCallHptInvalidateNoSyncICache, hpteIndex);
	return compressedStatus;
}