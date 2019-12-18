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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct ubifs_data_node {int /*<<< orphan*/  size; int /*<<< orphan*/  compr_type; int /*<<< orphan*/  data; TYPE_1__ ch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBIFS_BLOCK_SIZE ; 
 int UBIFS_DATA_NODE_SZ ; 
 int WORST_COMPR_FACTOR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_compress (void*,int,int /*<<< orphan*/ *,int*,int*) ; 
 int ubifs_decompress (int /*<<< orphan*/ *,int,void*,int*,int) ; 

__attribute__((used)) static int recomp_data_node(struct ubifs_data_node *dn, int *new_len)
{
	void *buf;
	int err, len, compr_type, out_len;

	out_len = le32_to_cpu(dn->size);
	buf = kmalloc(out_len * WORST_COMPR_FACTOR, GFP_NOFS);
	if (!buf)
		return -ENOMEM;

	len = le32_to_cpu(dn->ch.len) - UBIFS_DATA_NODE_SZ;
	compr_type = le16_to_cpu(dn->compr_type);
	err = ubifs_decompress(&dn->data, len, buf, &out_len, compr_type);
	if (err)
		goto out;

	ubifs_compress(buf, *new_len, &dn->data, &out_len, &compr_type);
	ubifs_assert(out_len <= UBIFS_BLOCK_SIZE);
	dn->compr_type = cpu_to_le16(compr_type);
	dn->size = cpu_to_le32(*new_len);
	*new_len = UBIFS_DATA_NODE_SZ + out_len;
out:
	kfree(buf);
	return err;
}