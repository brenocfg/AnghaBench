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

/* Variables and functions */

__attribute__((used)) static inline void bip_ipn_swap(u8 *d, const u8 *s)
{
	*d++ = s[5];
	*d++ = s[4];
	*d++ = s[3];
	*d++ = s[2];
	*d++ = s[1];
	*d = s[0];
}