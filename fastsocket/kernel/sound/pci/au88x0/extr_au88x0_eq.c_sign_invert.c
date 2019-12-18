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

/* Variables and functions */

__attribute__((used)) static inline u16 sign_invert(u16 a)
{
	/* -(-32768) -> -32768 so we do -(-32768) -> 32767 to make the result positive */
	if (a == (u16)-32768)
		return 32767;
	else
		return -a;
}