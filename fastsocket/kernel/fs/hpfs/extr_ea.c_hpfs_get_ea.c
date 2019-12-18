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
struct fnode {int ea_size_l; int ea_anode; int /*<<< orphan*/  ea_secno; } ;
struct extended_attribute {int valuelen; int namelen; int /*<<< orphan*/  anode; scalar_t__ indirect; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ea_data (struct extended_attribute*) ; 
 int ea_len (struct extended_attribute*) ; 
 int /*<<< orphan*/  ea_sec (struct extended_attribute*) ; 
 struct extended_attribute* fnode_ea (struct fnode*) ; 
 struct extended_attribute* fnode_end_ea (struct fnode*) ; 
 char* get_indirect_ea (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hpfs_ea_read (struct super_block*,int /*<<< orphan*/ ,int,unsigned int,int,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct extended_attribute* next_ea (struct extended_attribute*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

char *hpfs_get_ea(struct super_block *s, struct fnode *fnode, char *key, int *size)
{
	char *ret;
	unsigned pos;
	int ano, len;
	secno a;
	struct extended_attribute *ea;
	struct extended_attribute *ea_end = fnode_end_ea(fnode);
	for (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		if (!strcmp(ea->name, key)) {
			if (ea->indirect)
				return get_indirect_ea(s, ea->anode, ea_sec(ea), *size = ea_len(ea));
			if (!(ret = kmalloc((*size = ea->valuelen) + 1, GFP_NOFS))) {
				printk("HPFS: out of memory for EA\n");
				return NULL;
			}
			memcpy(ret, ea_data(ea), ea->valuelen);
			ret[ea->valuelen] = 0;
			return ret;
		}
	a = fnode->ea_secno;
	len = fnode->ea_size_l;
	ano = fnode->ea_anode;
	pos = 0;
	while (pos < len) {
		char ex[4 + 255 + 1 + 8];
		ea = (struct extended_attribute *)ex;
		if (pos + 4 > len) {
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			return NULL;
		}
		if (hpfs_ea_read(s, a, ano, pos, 4, ex)) return NULL;
		if (hpfs_ea_read(s, a, ano, pos + 4, ea->namelen + 1 + (ea->indirect ? 8 : 0), ex + 4))
			return NULL;
		if (!strcmp(ea->name, key)) {
			if (ea->indirect)
				return get_indirect_ea(s, ea->anode, ea_sec(ea), *size = ea_len(ea));
			if (!(ret = kmalloc((*size = ea->valuelen) + 1, GFP_NOFS))) {
				printk("HPFS: out of memory for EA\n");
				return NULL;
			}
			if (hpfs_ea_read(s, a, ano, pos + 4 + ea->namelen + 1, ea->valuelen, ret)) {
				kfree(ret);
				return NULL;
			}
			ret[ea->valuelen] = 0;
			return ret;
		}
		pos += ea->namelen + ea->valuelen + 5;
	}
	return NULL;
}