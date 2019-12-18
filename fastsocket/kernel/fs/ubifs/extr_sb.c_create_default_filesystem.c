#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct TYPE_5__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_sb_node {TYPE_2__ ch; void* flags; void* size; void* mode; scalar_t__ mtime_nsec; scalar_t__ ctime_nsec; scalar_t__ atime_nsec; void* mtime_sec; void* ctime_sec; void* atime_sec; void* nlink; void* creat_sqnum; int /*<<< orphan*/  key; void* child_cnt; void* total_used; void* total_dark; void* total_dirty; void* total_free; void* leb_cnt; void* idx_lebs; void* empty_lebs; void* lscan_lnum; void* lsave_offs; void* lsave_lnum; void* ltab_offs; void* ltab_lnum; void* nhead_offs; void* nhead_lnum; void* lpt_offs; void* lpt_lnum; void* index_size; void* ihead_offs; void* ihead_lnum; void* gc_lnum; void* root_len; scalar_t__ root_offs; void* root_lnum; scalar_t__ cmt_no; void* highest_inum; void* log_lnum; void* ro_compat_version; void* rp_size; int /*<<< orphan*/  uuid; void* default_compr; void* time_gran; void* fmt_version; void* lsave_cnt; void* fanout; void* jhead_cnt; void* orph_lebs; void* lpt_lebs; void* log_lebs; void* max_bud_bytes; void* max_leb_cnt; void* leb_size; void* min_io_size; int /*<<< orphan*/  key_hash; } ;
struct ubifs_mst_node {TYPE_2__ ch; void* flags; void* size; void* mode; scalar_t__ mtime_nsec; scalar_t__ ctime_nsec; scalar_t__ atime_nsec; void* mtime_sec; void* ctime_sec; void* atime_sec; void* nlink; void* creat_sqnum; int /*<<< orphan*/  key; void* child_cnt; void* total_used; void* total_dark; void* total_dirty; void* total_free; void* leb_cnt; void* idx_lebs; void* empty_lebs; void* lscan_lnum; void* lsave_offs; void* lsave_lnum; void* ltab_offs; void* ltab_lnum; void* nhead_offs; void* nhead_lnum; void* lpt_offs; void* lpt_lnum; void* index_size; void* ihead_offs; void* ihead_lnum; void* gc_lnum; void* root_len; scalar_t__ root_offs; void* root_lnum; scalar_t__ cmt_no; void* highest_inum; void* log_lnum; void* ro_compat_version; void* rp_size; int /*<<< orphan*/  uuid; void* default_compr; void* time_gran; void* fmt_version; void* lsave_cnt; void* fanout; void* jhead_cnt; void* orph_lebs; void* lpt_lebs; void* log_lebs; void* max_bud_bytes; void* max_leb_cnt; void* leb_size; void* min_io_size; int /*<<< orphan*/  key_hash; } ;
struct ubifs_ino_node {TYPE_2__ ch; void* flags; void* size; void* mode; scalar_t__ mtime_nsec; scalar_t__ ctime_nsec; scalar_t__ atime_nsec; void* mtime_sec; void* ctime_sec; void* atime_sec; void* nlink; void* creat_sqnum; int /*<<< orphan*/  key; void* child_cnt; void* total_used; void* total_dark; void* total_dirty; void* total_free; void* leb_cnt; void* idx_lebs; void* empty_lebs; void* lscan_lnum; void* lsave_offs; void* lsave_lnum; void* ltab_offs; void* ltab_lnum; void* nhead_offs; void* nhead_lnum; void* lpt_offs; void* lpt_lnum; void* index_size; void* ihead_offs; void* ihead_lnum; void* gc_lnum; void* root_len; scalar_t__ root_offs; void* root_lnum; scalar_t__ cmt_no; void* highest_inum; void* log_lnum; void* ro_compat_version; void* rp_size; int /*<<< orphan*/  uuid; void* default_compr; void* time_gran; void* fmt_version; void* lsave_cnt; void* fanout; void* jhead_cnt; void* orph_lebs; void* lpt_lebs; void* log_lebs; void* max_bud_bytes; void* max_leb_cnt; void* leb_size; void* min_io_size; int /*<<< orphan*/  key_hash; } ;
struct TYPE_4__ {int compr_type; scalar_t__ override_compr; } ;
struct ubifs_info {int leb_cnt; int leb_size; int ref_node_alsz; int lsave_cnt; int max_leb_cnt; int min_io_size; int mst_node_alsz; int lpt_lnum; int lpt_offs; int nhead_lnum; int nhead_offs; int ltab_lnum; int ltab_offs; int lsave_lnum; int lsave_offs; int main_lebs; int dark_wm; int max_sqnum; int /*<<< orphan*/  key_hash; int /*<<< orphan*/  key_fmt; TYPE_1__ mount_opts; int /*<<< orphan*/  key_len; } ;
struct ubifs_idx_node {TYPE_2__ ch; void* flags; void* size; void* mode; scalar_t__ mtime_nsec; scalar_t__ ctime_nsec; scalar_t__ atime_nsec; void* mtime_sec; void* ctime_sec; void* atime_sec; void* nlink; void* creat_sqnum; int /*<<< orphan*/  key; void* child_cnt; void* total_used; void* total_dark; void* total_dirty; void* total_free; void* leb_cnt; void* idx_lebs; void* empty_lebs; void* lscan_lnum; void* lsave_offs; void* lsave_lnum; void* ltab_offs; void* ltab_lnum; void* nhead_offs; void* nhead_lnum; void* lpt_offs; void* lpt_lnum; void* index_size; void* ihead_offs; void* ihead_lnum; void* gc_lnum; void* root_len; scalar_t__ root_offs; void* root_lnum; scalar_t__ cmt_no; void* highest_inum; void* log_lnum; void* ro_compat_version; void* rp_size; int /*<<< orphan*/  uuid; void* default_compr; void* time_gran; void* fmt_version; void* lsave_cnt; void* fanout; void* jhead_cnt; void* orph_lebs; void* lpt_lebs; void* log_lebs; void* max_bud_bytes; void* max_leb_cnt; void* leb_size; void* min_io_size; int /*<<< orphan*/  key_hash; } ;
struct ubifs_cs_node {TYPE_2__ ch; void* flags; void* size; void* mode; scalar_t__ mtime_nsec; scalar_t__ ctime_nsec; scalar_t__ atime_nsec; void* mtime_sec; void* ctime_sec; void* atime_sec; void* nlink; void* creat_sqnum; int /*<<< orphan*/  key; void* child_cnt; void* total_used; void* total_dark; void* total_dirty; void* total_free; void* leb_cnt; void* idx_lebs; void* empty_lebs; void* lscan_lnum; void* lsave_offs; void* lsave_lnum; void* ltab_offs; void* ltab_lnum; void* nhead_offs; void* nhead_lnum; void* lpt_offs; void* lpt_lnum; void* index_size; void* ihead_offs; void* ihead_lnum; void* gc_lnum; void* root_len; scalar_t__ root_offs; void* root_lnum; scalar_t__ cmt_no; void* highest_inum; void* log_lnum; void* ro_compat_version; void* rp_size; int /*<<< orphan*/  uuid; void* default_compr; void* time_gran; void* fmt_version; void* lsave_cnt; void* fanout; void* jhead_cnt; void* orph_lebs; void* lpt_lebs; void* log_lebs; void* max_bud_bytes; void* max_leb_cnt; void* leb_size; void* min_io_size; int /*<<< orphan*/  key_hash; } ;
struct ubifs_branch {void* len; void* lnum; int /*<<< orphan*/  key; } ;
typedef  void* __le64 ;
struct TYPE_6__ {int tv_sec; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 TYPE_3__ CURRENT_TIME_SEC ; 
 int DEFAULT_DATA_LEB ; 
 int DEFAULT_FANOUT ; 
 int DEFAULT_GC_LEB ; 
 int DEFAULT_IDX_LEB ; 
 int DEFAULT_JHEADS_CNT ; 
 int DEFAULT_JNL_PERCENT ; 
 int DEFAULT_LSAVE_CNT ; 
 int DEFAULT_MAX_JNL ; 
 long long DEFAULT_MAX_RP_SIZE ; 
 long long DEFAULT_RP_PERCENT ; 
 int DEFAULT_TIME_GRAN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int S_IXUGO ; 
 int UBIFS_COMPR_FL ; 
 int UBIFS_COMPR_LZO ; 
 int /*<<< orphan*/  UBIFS_CS_NODE ; 
 int UBIFS_CS_NODE_SZ ; 
 int UBIFS_FIRST_INO ; 
 int UBIFS_FLG_BIGLPT ; 
 int UBIFS_FORMAT_VERSION ; 
 int /*<<< orphan*/  UBIFS_IDX_NODE ; 
 int /*<<< orphan*/  UBIFS_INO_NODE ; 
 int UBIFS_INO_NODE_SZ ; 
 int /*<<< orphan*/  UBIFS_KEY_HASH_R5 ; 
 int UBIFS_LOG_LNUM ; 
 int UBIFS_MIN_BUD_LEBS ; 
 int UBIFS_MIN_JNL_LEBS ; 
 int UBIFS_MIN_LEB_CNT ; 
 int UBIFS_MIN_ORPH_LEBS ; 
 int UBIFS_MST_LEBS ; 
 int UBIFS_MST_LNUM ; 
 int /*<<< orphan*/  UBIFS_MST_NODE ; 
 int UBIFS_MST_NODE_SZ ; 
 int /*<<< orphan*/  UBIFS_ROOT_INO ; 
 int UBIFS_RO_COMPAT_VERSION ; 
 int /*<<< orphan*/  UBIFS_SB_LEBS ; 
 int /*<<< orphan*/  UBIFS_SB_NODE ; 
 int UBIFS_SB_NODE_SZ ; 
 int /*<<< orphan*/  UBIFS_SIMPLE_KEY_FMT ; 
 int /*<<< orphan*/  UBIFS_SK_LEN ; 
 int /*<<< orphan*/  UBI_LONGTERM ; 
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 long long div_u64 (long long,int) ; 
 int /*<<< orphan*/  generate_random_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_key_init_flash (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_r5_hash ; 
 int /*<<< orphan*/  key_write_idx (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubifs_sb_node*) ; 
 struct ubifs_sb_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ubifs_create_dflt_lpt (struct ubifs_info*,int*,int,int*,int*) ; 
 struct ubifs_branch* ubifs_idx_branch (struct ubifs_info*,struct ubifs_sb_node*,int /*<<< orphan*/ ) ; 
 int ubifs_idx_node_sz (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_msg (char*) ; 
 int ubifs_write_node (struct ubifs_info*,struct ubifs_sb_node*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_default_filesystem(struct ubifs_info *c)
{
	struct ubifs_sb_node *sup;
	struct ubifs_mst_node *mst;
	struct ubifs_idx_node *idx;
	struct ubifs_branch *br;
	struct ubifs_ino_node *ino;
	struct ubifs_cs_node *cs;
	union ubifs_key key;
	int err, tmp, jnl_lebs, log_lebs, max_buds, main_lebs, main_first;
	int lpt_lebs, lpt_first, orph_lebs, big_lpt, ino_waste, sup_flags = 0;
	int min_leb_cnt = UBIFS_MIN_LEB_CNT;
	long long tmp64, main_bytes;
	__le64 tmp_le64;

	/* Some functions called from here depend on the @c->key_len filed */
	c->key_len = UBIFS_SK_LEN;

	/*
	 * First of all, we have to calculate default file-system geometry -
	 * log size, journal size, etc.
	 */
	if (c->leb_cnt < 0x7FFFFFFF / DEFAULT_JNL_PERCENT)
		/* We can first multiply then divide and have no overflow */
		jnl_lebs = c->leb_cnt * DEFAULT_JNL_PERCENT / 100;
	else
		jnl_lebs = (c->leb_cnt / 100) * DEFAULT_JNL_PERCENT;

	if (jnl_lebs < UBIFS_MIN_JNL_LEBS)
		jnl_lebs = UBIFS_MIN_JNL_LEBS;
	if (jnl_lebs * c->leb_size > DEFAULT_MAX_JNL)
		jnl_lebs = DEFAULT_MAX_JNL / c->leb_size;

	/*
	 * The log should be large enough to fit reference nodes for all bud
	 * LEBs. Because buds do not have to start from the beginning of LEBs
	 * (half of the LEB may contain committed data), the log should
	 * generally be larger, make it twice as large.
	 */
	tmp = 2 * (c->ref_node_alsz * jnl_lebs) + c->leb_size - 1;
	log_lebs = tmp / c->leb_size;
	/* Plus one LEB reserved for commit */
	log_lebs += 1;
	if (c->leb_cnt - min_leb_cnt > 8) {
		/* And some extra space to allow writes while committing */
		log_lebs += 1;
		min_leb_cnt += 1;
	}

	max_buds = jnl_lebs - log_lebs;
	if (max_buds < UBIFS_MIN_BUD_LEBS)
		max_buds = UBIFS_MIN_BUD_LEBS;

	/*
	 * Orphan nodes are stored in a separate area. One node can store a lot
	 * of orphan inode numbers, but when new orphan comes we just add a new
	 * orphan node. At some point the nodes are consolidated into one
	 * orphan node.
	 */
	orph_lebs = UBIFS_MIN_ORPH_LEBS;
#ifdef CONFIG_UBIFS_FS_DEBUG
	if (c->leb_cnt - min_leb_cnt > 1)
		/*
		 * For debugging purposes it is better to have at least 2
		 * orphan LEBs, because the orphan subsystem would need to do
		 * consolidations and would be stressed more.
		 */
		orph_lebs += 1;
#endif

	main_lebs = c->leb_cnt - UBIFS_SB_LEBS - UBIFS_MST_LEBS - log_lebs;
	main_lebs -= orph_lebs;

	lpt_first = UBIFS_LOG_LNUM + log_lebs;
	c->lsave_cnt = DEFAULT_LSAVE_CNT;
	c->max_leb_cnt = c->leb_cnt;
	err = ubifs_create_dflt_lpt(c, &main_lebs, lpt_first, &lpt_lebs,
				    &big_lpt);
	if (err)
		return err;

	dbg_gen("LEB Properties Tree created (LEBs %d-%d)", lpt_first,
		lpt_first + lpt_lebs - 1);

	main_first = c->leb_cnt - main_lebs;

	/* Create default superblock */
	tmp = ALIGN(UBIFS_SB_NODE_SZ, c->min_io_size);
	sup = kzalloc(tmp, GFP_KERNEL);
	if (!sup)
		return -ENOMEM;

	tmp64 = (long long)max_buds * c->leb_size;
	if (big_lpt)
		sup_flags |= UBIFS_FLG_BIGLPT;

	sup->ch.node_type  = UBIFS_SB_NODE;
	sup->key_hash      = UBIFS_KEY_HASH_R5;
	sup->flags         = cpu_to_le32(sup_flags);
	sup->min_io_size   = cpu_to_le32(c->min_io_size);
	sup->leb_size      = cpu_to_le32(c->leb_size);
	sup->leb_cnt       = cpu_to_le32(c->leb_cnt);
	sup->max_leb_cnt   = cpu_to_le32(c->max_leb_cnt);
	sup->max_bud_bytes = cpu_to_le64(tmp64);
	sup->log_lebs      = cpu_to_le32(log_lebs);
	sup->lpt_lebs      = cpu_to_le32(lpt_lebs);
	sup->orph_lebs     = cpu_to_le32(orph_lebs);
	sup->jhead_cnt     = cpu_to_le32(DEFAULT_JHEADS_CNT);
	sup->fanout        = cpu_to_le32(DEFAULT_FANOUT);
	sup->lsave_cnt     = cpu_to_le32(c->lsave_cnt);
	sup->fmt_version   = cpu_to_le32(UBIFS_FORMAT_VERSION);
	sup->time_gran     = cpu_to_le32(DEFAULT_TIME_GRAN);
	if (c->mount_opts.override_compr)
		sup->default_compr = cpu_to_le16(c->mount_opts.compr_type);
	else
		sup->default_compr = cpu_to_le16(UBIFS_COMPR_LZO);

	generate_random_uuid(sup->uuid);

	main_bytes = (long long)main_lebs * c->leb_size;
	tmp64 = div_u64(main_bytes * DEFAULT_RP_PERCENT, 100);
	if (tmp64 > DEFAULT_MAX_RP_SIZE)
		tmp64 = DEFAULT_MAX_RP_SIZE;
	sup->rp_size = cpu_to_le64(tmp64);
	sup->ro_compat_version = cpu_to_le32(UBIFS_RO_COMPAT_VERSION);

	err = ubifs_write_node(c, sup, UBIFS_SB_NODE_SZ, 0, 0, UBI_LONGTERM);
	kfree(sup);
	if (err)
		return err;

	dbg_gen("default superblock created at LEB 0:0");

	/* Create default master node */
	mst = kzalloc(c->mst_node_alsz, GFP_KERNEL);
	if (!mst)
		return -ENOMEM;

	mst->ch.node_type = UBIFS_MST_NODE;
	mst->log_lnum     = cpu_to_le32(UBIFS_LOG_LNUM);
	mst->highest_inum = cpu_to_le64(UBIFS_FIRST_INO);
	mst->cmt_no       = 0;
	mst->root_lnum    = cpu_to_le32(main_first + DEFAULT_IDX_LEB);
	mst->root_offs    = 0;
	tmp = ubifs_idx_node_sz(c, 1);
	mst->root_len     = cpu_to_le32(tmp);
	mst->gc_lnum      = cpu_to_le32(main_first + DEFAULT_GC_LEB);
	mst->ihead_lnum   = cpu_to_le32(main_first + DEFAULT_IDX_LEB);
	mst->ihead_offs   = cpu_to_le32(ALIGN(tmp, c->min_io_size));
	mst->index_size   = cpu_to_le64(ALIGN(tmp, 8));
	mst->lpt_lnum     = cpu_to_le32(c->lpt_lnum);
	mst->lpt_offs     = cpu_to_le32(c->lpt_offs);
	mst->nhead_lnum   = cpu_to_le32(c->nhead_lnum);
	mst->nhead_offs   = cpu_to_le32(c->nhead_offs);
	mst->ltab_lnum    = cpu_to_le32(c->ltab_lnum);
	mst->ltab_offs    = cpu_to_le32(c->ltab_offs);
	mst->lsave_lnum   = cpu_to_le32(c->lsave_lnum);
	mst->lsave_offs   = cpu_to_le32(c->lsave_offs);
	mst->lscan_lnum   = cpu_to_le32(main_first);
	mst->empty_lebs   = cpu_to_le32(main_lebs - 2);
	mst->idx_lebs     = cpu_to_le32(1);
	mst->leb_cnt      = cpu_to_le32(c->leb_cnt);

	/* Calculate lprops statistics */
	tmp64 = main_bytes;
	tmp64 -= ALIGN(ubifs_idx_node_sz(c, 1), c->min_io_size);
	tmp64 -= ALIGN(UBIFS_INO_NODE_SZ, c->min_io_size);
	mst->total_free = cpu_to_le64(tmp64);

	tmp64 = ALIGN(ubifs_idx_node_sz(c, 1), c->min_io_size);
	ino_waste = ALIGN(UBIFS_INO_NODE_SZ, c->min_io_size) -
			  UBIFS_INO_NODE_SZ;
	tmp64 += ino_waste;
	tmp64 -= ALIGN(ubifs_idx_node_sz(c, 1), 8);
	mst->total_dirty = cpu_to_le64(tmp64);

	/*  The indexing LEB does not contribute to dark space */
	tmp64 = (c->main_lebs - 1) * c->dark_wm;
	mst->total_dark = cpu_to_le64(tmp64);

	mst->total_used = cpu_to_le64(UBIFS_INO_NODE_SZ);

	err = ubifs_write_node(c, mst, UBIFS_MST_NODE_SZ, UBIFS_MST_LNUM, 0,
			       UBI_UNKNOWN);
	if (err) {
		kfree(mst);
		return err;
	}
	err = ubifs_write_node(c, mst, UBIFS_MST_NODE_SZ, UBIFS_MST_LNUM + 1, 0,
			       UBI_UNKNOWN);
	kfree(mst);
	if (err)
		return err;

	dbg_gen("default master node created at LEB %d:0", UBIFS_MST_LNUM);

	/* Create the root indexing node */
	tmp = ubifs_idx_node_sz(c, 1);
	idx = kzalloc(ALIGN(tmp, c->min_io_size), GFP_KERNEL);
	if (!idx)
		return -ENOMEM;

	c->key_fmt = UBIFS_SIMPLE_KEY_FMT;
	c->key_hash = key_r5_hash;

	idx->ch.node_type = UBIFS_IDX_NODE;
	idx->child_cnt = cpu_to_le16(1);
	ino_key_init(c, &key, UBIFS_ROOT_INO);
	br = ubifs_idx_branch(c, idx, 0);
	key_write_idx(c, &key, &br->key);
	br->lnum = cpu_to_le32(main_first + DEFAULT_DATA_LEB);
	br->len  = cpu_to_le32(UBIFS_INO_NODE_SZ);
	err = ubifs_write_node(c, idx, tmp, main_first + DEFAULT_IDX_LEB, 0,
			       UBI_UNKNOWN);
	kfree(idx);
	if (err)
		return err;

	dbg_gen("default root indexing node created LEB %d:0",
		main_first + DEFAULT_IDX_LEB);

	/* Create default root inode */
	tmp = ALIGN(UBIFS_INO_NODE_SZ, c->min_io_size);
	ino = kzalloc(tmp, GFP_KERNEL);
	if (!ino)
		return -ENOMEM;

	ino_key_init_flash(c, &ino->key, UBIFS_ROOT_INO);
	ino->ch.node_type = UBIFS_INO_NODE;
	ino->creat_sqnum = cpu_to_le64(++c->max_sqnum);
	ino->nlink = cpu_to_le32(2);
	tmp_le64 = cpu_to_le64(CURRENT_TIME_SEC.tv_sec);
	ino->atime_sec   = tmp_le64;
	ino->ctime_sec   = tmp_le64;
	ino->mtime_sec   = tmp_le64;
	ino->atime_nsec  = 0;
	ino->ctime_nsec  = 0;
	ino->mtime_nsec  = 0;
	ino->mode = cpu_to_le32(S_IFDIR | S_IRUGO | S_IWUSR | S_IXUGO);
	ino->size = cpu_to_le64(UBIFS_INO_NODE_SZ);

	/* Set compression enabled by default */
	ino->flags = cpu_to_le32(UBIFS_COMPR_FL);

	err = ubifs_write_node(c, ino, UBIFS_INO_NODE_SZ,
			       main_first + DEFAULT_DATA_LEB, 0,
			       UBI_UNKNOWN);
	kfree(ino);
	if (err)
		return err;

	dbg_gen("root inode created at LEB %d:0",
		main_first + DEFAULT_DATA_LEB);

	/*
	 * The first node in the log has to be the commit start node. This is
	 * always the case during normal file-system operation. Write a fake
	 * commit start node to the log.
	 */
	tmp = ALIGN(UBIFS_CS_NODE_SZ, c->min_io_size);
	cs = kzalloc(tmp, GFP_KERNEL);
	if (!cs)
		return -ENOMEM;

	cs->ch.node_type = UBIFS_CS_NODE;
	err = ubifs_write_node(c, cs, UBIFS_CS_NODE_SZ, UBIFS_LOG_LNUM,
			       0, UBI_UNKNOWN);
	kfree(cs);

	ubifs_msg("default file-system created");
	return 0;
}