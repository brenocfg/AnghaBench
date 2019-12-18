#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int u16 ;
struct super_block {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  fs64 ;
typedef  scalar_t__ befs_off_t ;
typedef  int /*<<< orphan*/  befs_data_stream ;
struct TYPE_12__ {scalar_t__ root_node_ptr; } ;
typedef  TYPE_2__ befs_btree_super ;
struct TYPE_11__ {scalar_t__ all_key_count; scalar_t__ right; } ;
struct TYPE_13__ {int /*<<< orphan*/ * bh; TYPE_1__ head; } ;
typedef  TYPE_3__ befs_btree_node ;

/* Variables and functions */
 int BEFS_BT_EMPTY ; 
 int BEFS_BT_END ; 
 int BEFS_ERR ; 
 scalar_t__ BEFS_OK ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 char* befs_bt_get_key (struct super_block*,TYPE_3__*,int,int*) ; 
 scalar_t__ befs_bt_inval ; 
 scalar_t__ befs_bt_read_node (struct super_block*,int /*<<< orphan*/ *,TYPE_3__*,scalar_t__) ; 
 scalar_t__ befs_bt_read_super (struct super_block*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * befs_bt_valarray (TYPE_3__*) ; 
 int befs_btree_seekleaf (struct super_block*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 scalar_t__ fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int
befs_btree_read(struct super_block *sb, befs_data_stream * ds,
		loff_t key_no, size_t bufsize, char *keybuf, size_t * keysize,
		befs_off_t * value)
{
	befs_btree_node *this_node;
	befs_btree_super bt_super;
	befs_off_t node_off = 0;
	int cur_key;
	fs64 *valarray;
	char *keystart;
	u16 keylen;
	int res;

	uint key_sum = 0;

	befs_debug(sb, "---> befs_btree_read()");

	if (befs_bt_read_super(sb, ds, &bt_super) != BEFS_OK) {
		befs_error(sb,
			   "befs_btree_read() failed to read index superblock");
		goto error;
	}

	if ((this_node = (befs_btree_node *)
	     kmalloc(sizeof (befs_btree_node), GFP_NOFS)) == NULL) {
		befs_error(sb, "befs_btree_read() failed to allocate %u "
			   "bytes of memory", sizeof (befs_btree_node));
		goto error;
	}

	node_off = bt_super.root_node_ptr;
	this_node->bh = NULL;

	/* seeks down to first leafnode, reads it into this_node */
	res = befs_btree_seekleaf(sb, ds, &bt_super, this_node, &node_off);
	if (res == BEFS_BT_EMPTY) {
		brelse(this_node->bh);
		kfree(this_node);
		*value = 0;
		*keysize = 0;
		befs_debug(sb, "<--- befs_btree_read() Tree is EMPTY");
		return BEFS_BT_EMPTY;
	} else if (res == BEFS_ERR) {
		goto error_alloc;
	}

	/* find the leaf node containing the key_no key */

	while (key_sum + this_node->head.all_key_count <= key_no) {

		/* no more nodes to look in: key_no is too large */
		if (this_node->head.right == befs_bt_inval) {
			*keysize = 0;
			*value = 0;
			befs_debug(sb,
				   "<--- befs_btree_read() END of keys at %Lu",
				   key_sum + this_node->head.all_key_count);
			brelse(this_node->bh);
			kfree(this_node);
			return BEFS_BT_END;
		}

		key_sum += this_node->head.all_key_count;
		node_off = this_node->head.right;

		if (befs_bt_read_node(sb, ds, this_node, node_off) != BEFS_OK) {
			befs_error(sb, "befs_btree_read() failed to read "
				   "node at %Lu", node_off);
			goto error_alloc;
		}
	}

	/* how many keys into this_node is key_no */
	cur_key = key_no - key_sum;

	/* get pointers to datastructures within the node body */
	valarray = befs_bt_valarray(this_node);

	keystart = befs_bt_get_key(sb, this_node, cur_key, &keylen);

	befs_debug(sb, "Read [%Lu,%d]: keysize %d", node_off, cur_key, keylen);

	if (bufsize < keylen + 1) {
		befs_error(sb, "befs_btree_read() keybuf too small (%u) "
			   "for key of size %d", bufsize, keylen);
		brelse(this_node->bh);
		goto error_alloc;
	};

	strncpy(keybuf, keystart, keylen);
	*value = fs64_to_cpu(sb, valarray[cur_key]);
	*keysize = keylen;
	keybuf[keylen] = '\0';

	befs_debug(sb, "Read [%Lu,%d]: Key \"%.*s\", Value %Lu", node_off,
		   cur_key, keylen, keybuf, *value);

	brelse(this_node->bh);
	kfree(this_node);

	befs_debug(sb, "<--- befs_btree_read()");

	return BEFS_OK;

      error_alloc:
	kfree(this_node);

      error:
	*keysize = 0;
	*value = 0;
	befs_debug(sb, "<--- befs_btree_read() ERROR");
	return BEFS_ERR;
}