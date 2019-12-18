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
typedef  int u8 ;

/* Variables and functions */
 unsigned long u3_ht_cfa0 (int,int) ; 

__attribute__((used)) static unsigned long u3_ht_cfa1(u8 bus, u8 devfn, u8 off)
{
	return u3_ht_cfa0(devfn, off) + (bus << 16) + 0x01000000UL;
}