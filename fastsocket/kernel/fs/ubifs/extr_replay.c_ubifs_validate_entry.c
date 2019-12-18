#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct ubifs_dent_node {scalar_t__ type; scalar_t__* name; int /*<<< orphan*/  inum; TYPE_1__ ch; int /*<<< orphan*/  nlen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_INUM ; 
 int UBIFS_DENT_KEY ; 
 scalar_t__ UBIFS_DENT_NODE_SZ ; 
 scalar_t__ UBIFS_ITYPES_CNT ; 
 int UBIFS_MAX_NLEN ; 
 int UBIFS_XENT_KEY ; 
 int key_type_flash (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int strnlen (scalar_t__*,int) ; 
 int /*<<< orphan*/  ubifs_err (char*,...) ; 

int ubifs_validate_entry(struct ubifs_info *c,
			 const struct ubifs_dent_node *dent)
{
	int key_type = key_type_flash(c, dent->key);
	int nlen = le16_to_cpu(dent->nlen);

	if (le32_to_cpu(dent->ch.len) != nlen + UBIFS_DENT_NODE_SZ + 1 ||
	    dent->type >= UBIFS_ITYPES_CNT ||
	    nlen > UBIFS_MAX_NLEN || dent->name[nlen] != 0 ||
	    strnlen(dent->name, nlen) != nlen ||
	    le64_to_cpu(dent->inum) > MAX_INUM) {
		ubifs_err("bad %s node", key_type == UBIFS_DENT_KEY ?
			  "directory entry" : "extended attribute entry");
		return -EINVAL;
	}

	if (key_type != UBIFS_DENT_KEY && key_type != UBIFS_XENT_KEY) {
		ubifs_err("bad key type %d", key_type);
		return -EINVAL;
	}

	return 0;
}