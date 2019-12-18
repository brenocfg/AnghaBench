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
struct ubifs_dent_node {int /*<<< orphan*/  name; int /*<<< orphan*/  nlen; } ;
struct qstr {int len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int do_lookup_nm (struct ubifs_info*,union ubifs_key const*,void*,struct qstr const*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ubifs_tnc_lookup (struct ubifs_info*,union ubifs_key const*,void*) ; 

int ubifs_tnc_lookup_nm(struct ubifs_info *c, const union ubifs_key *key,
			void *node, const struct qstr *nm)
{
	int err, len;
	const struct ubifs_dent_node *dent = node;

	/*
	 * We assume that in most of the cases there are no name collisions and
	 * 'ubifs_tnc_lookup()' returns us the right direntry.
	 */
	err = ubifs_tnc_lookup(c, key, node);
	if (err)
		return err;

	len = le16_to_cpu(dent->nlen);
	if (nm->len == len && !memcmp(dent->name, nm->name, len))
		return 0;

	/*
	 * Unluckily, there are hash collisions and we have to iterate over
	 * them look at each direntry with colliding name hash sequentially.
	 */
	return do_lookup_nm(c, key, node, nm);
}