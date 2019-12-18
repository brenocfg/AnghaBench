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
struct super_block {int dummy; } ;

/* Variables and functions */
 unsigned long L1_CACHE_SHIFT ; 
 int MAXQUOTAS ; 
 unsigned long dq_hash_bits ; 
 unsigned long dq_hash_mask ; 

__attribute__((used)) static inline unsigned int
hashfn(const struct super_block *sb, unsigned int id, int type)
{
	unsigned long tmp;

	tmp = (((unsigned long)sb>>L1_CACHE_SHIFT) ^ id) * (MAXQUOTAS - type);
	return (tmp + (tmp >> dq_hash_bits)) & dq_hash_mask;
}