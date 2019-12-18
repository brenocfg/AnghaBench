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

/* Variables and functions */
 int /*<<< orphan*/  F1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** Tm ; 
 int /*<<< orphan*/ ** Tr ; 

__attribute__((used)) static void W(u32 *key, unsigned int i) {
	u32 I;
	key[6] ^= F1(key[7], Tr[i % 4][0], Tm[i][0]);
	key[5] ^= F2(key[6], Tr[i % 4][1], Tm[i][1]);
	key[4] ^= F3(key[5], Tr[i % 4][2], Tm[i][2]);
	key[3] ^= F1(key[4], Tr[i % 4][3], Tm[i][3]);
	key[2] ^= F2(key[3], Tr[i % 4][4], Tm[i][4]);
	key[1] ^= F3(key[2], Tr[i % 4][5], Tm[i][5]);
	key[0] ^= F1(key[1], Tr[i % 4][6], Tm[i][6]);	
	key[7] ^= F2(key[0], Tr[i % 4][7], Tm[i][7]);
}