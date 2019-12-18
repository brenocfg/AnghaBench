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
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */

__attribute__((used)) static inline int memcmp_fs(const void *s1, addr_t s2, size_t len)
{
	u8 diff;
	asm volatile("fs; repe; cmpsb; setnz %0"
		     : "=qm" (diff), "+D" (s1), "+S" (s2), "+c" (len));
	return diff;
}