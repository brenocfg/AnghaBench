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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__* S ; 

__attribute__((used)) static uint32_t
SubWord(uint32_t x)
{
	return ((uint32_t)S[x >> 24] << 24)
		| ((uint32_t)S[(x >> 16) & 0xFF] << 16)
		| ((uint32_t)S[(x >> 8) & 0xFF] << 8)
		| (uint32_t)S[x & 0xFF];
}