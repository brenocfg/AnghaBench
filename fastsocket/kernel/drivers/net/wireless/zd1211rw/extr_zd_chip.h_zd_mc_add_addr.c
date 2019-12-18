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
struct zd_mc_hash {int low; int high; } ;

/* Variables and functions */

__attribute__((used)) static inline void zd_mc_add_addr(struct zd_mc_hash *hash, u8 *addr)
{
	unsigned int i = addr[5] >> 2;
	if (i < 32) {
		hash->low |= 1 << i;
	} else {
		hash->high |= 1 << (i-32);
	}
}