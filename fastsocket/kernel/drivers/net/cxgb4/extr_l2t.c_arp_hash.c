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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int L2T_HASH_MASK ; 
 unsigned int jhash_2words (int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int arp_hash(const u32 *key, int ifindex)
{
	return jhash_2words(*key, ifindex, 0) & L2T_HASH_MASK;
}