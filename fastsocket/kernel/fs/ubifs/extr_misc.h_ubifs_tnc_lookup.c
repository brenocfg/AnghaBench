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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int ubifs_tnc_locate (struct ubifs_info*,union ubifs_key const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ubifs_tnc_lookup(struct ubifs_info *c,
				   const union ubifs_key *key, void *node)
{
	return ubifs_tnc_locate(c, key, node, NULL, NULL);
}