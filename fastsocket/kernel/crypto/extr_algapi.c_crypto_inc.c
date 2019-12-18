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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  crypto_inc_byte (int /*<<< orphan*/ *,unsigned int) ; 

void crypto_inc(u8 *a, unsigned int size)
{
	__be32 *b = (__be32 *)(a + size);
	u32 c;

	for (; size >= 4; size -= 4) {
		c = be32_to_cpu(*--b) + 1;
		*b = cpu_to_be32(c);
		if (c)
			return;
	}

	crypto_inc_byte(a, size);
}