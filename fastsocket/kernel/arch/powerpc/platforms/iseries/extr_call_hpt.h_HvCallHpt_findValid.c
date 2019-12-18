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
struct hash_pte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall3Ret16 (int /*<<< orphan*/ ,struct hash_pte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallHptFindValid ; 

__attribute__((used)) static inline u64 HvCallHpt_findValid(struct hash_pte *hpte, u64 vpn)
{
	return HvCall3Ret16(HvCallHptFindValid, hpte, vpn, 0, 0);
}