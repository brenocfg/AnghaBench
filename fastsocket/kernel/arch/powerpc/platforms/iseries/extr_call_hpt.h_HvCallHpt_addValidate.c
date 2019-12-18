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
typedef  int /*<<< orphan*/  u32 ;
struct hash_pte {int /*<<< orphan*/  r; int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallHptAddValidate ; 

__attribute__((used)) static inline void HvCallHpt_addValidate(u32 hpteIndex, u32 hBit,
					 struct hash_pte *hpte)
{
	HvCall4(HvCallHptAddValidate, hpteIndex, hBit, hpte->v, hpte->r);
}