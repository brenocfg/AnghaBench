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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_xor_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

void crypto_xor(u8 *dst, const u8 *src, unsigned int size)
{
	u32 *a = (u32 *)dst;
	u32 *b = (u32 *)src;

	for (; size >= 4; size -= 4)
		*a++ ^= *b++;

	crypto_xor_byte((u8 *)a, (u8 *)b, size);
}