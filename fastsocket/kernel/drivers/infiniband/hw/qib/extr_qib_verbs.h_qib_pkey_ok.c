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
typedef  int u16 ;
typedef  scalar_t__ __s16 ;

/* Variables and functions */

__attribute__((used)) static inline int qib_pkey_ok(u16 pkey1, u16 pkey2)
{
	u16 p1 = pkey1 & 0x7FFF;
	u16 p2 = pkey2 & 0x7FFF;

	/*
	 * Low 15 bits must be non-zero and match, and
	 * one of the two must be a full member.
	 */
	return p1 && p1 == p2 && ((__s16)pkey1 < 0 || (__s16)pkey2 < 0);
}