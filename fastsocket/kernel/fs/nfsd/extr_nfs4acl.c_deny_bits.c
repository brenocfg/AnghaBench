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
typedef  int u32 ;
struct posix_ace_state {int deny; int allow; } ;

/* Variables and functions */

__attribute__((used)) static inline void deny_bits(struct posix_ace_state *astate, u32 mask)
{
	/* Deny all bits in the mask not already allowed: */
	astate->deny |= mask & ~astate->allow;
}