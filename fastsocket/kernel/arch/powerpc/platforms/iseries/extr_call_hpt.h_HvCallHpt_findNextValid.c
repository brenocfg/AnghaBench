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
struct hash_pte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall3Ret16 (int /*<<< orphan*/ ,struct hash_pte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallHptFindNextValid ; 

__attribute__((used)) static inline u64 HvCallHpt_findNextValid(struct hash_pte *hpte, u32 hpteIndex,
		u8 bitson, u8 bitsoff)
{
	return HvCall3Ret16(HvCallHptFindNextValid, hpte, hpteIndex,
			bitson, bitsoff);
}