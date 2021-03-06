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
union ubifs_key {unsigned int* u32; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 unsigned int UBIFS_S_KEY_BLOCK_MASK ; 

__attribute__((used)) static inline unsigned int key_block(const struct ubifs_info *c,
				     const union ubifs_key *key)
{
	return key->u32[1] & UBIFS_S_KEY_BLOCK_MASK;
}