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
typedef  int u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tr32 (int) ; 

__attribute__((used)) static inline void tg3_rd32_loop(struct tg3 *tp, u32 *dst, u32 off, u32 len)
{
	int i;

	dst = (u32 *)((u8 *)dst + off);
	for (i = 0; i < len; i += sizeof(u32))
		*dst++ = tr32(off + i);
}