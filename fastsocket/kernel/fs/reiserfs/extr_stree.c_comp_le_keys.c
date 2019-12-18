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
struct reiserfs_key {int dummy; } ;

/* Variables and functions */
 int memcmp (struct reiserfs_key const*,struct reiserfs_key const*,int) ; 

inline int comp_le_keys(const struct reiserfs_key *k1,
			const struct reiserfs_key *k2)
{
	return memcmp(k1, k2, sizeof(struct reiserfs_key));
}