#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct jffs2_sb_info {int dummy; } ;
struct jffs2_readinode_info {scalar_t__ latest_ref; size_t mctime_ver; scalar_t__ latest_mctime; int /*<<< orphan*/  fds; TYPE_2__* mdata_tn; int /*<<< orphan*/  tn_root; } ;
struct jffs2_raw_inode {int /*<<< orphan*/  mode; void* csize; void* dsize; void* isize; void* mtime; void* ctime; void* version; void* node_crc; void* uid; void* gid; void* atime; } ;
struct jffs2_inode_info {char* target; TYPE_1__* inocache; int /*<<< orphan*/  fragtree; TYPE_5__* metadata; int /*<<< orphan*/  sem; int /*<<< orphan*/  dents; } ;
typedef  int /*<<< orphan*/  rii ;
struct TYPE_11__ {scalar_t__ raw; } ;
struct TYPE_10__ {TYPE_5__* node; } ;
struct TYPE_9__ {TYPE_5__* fn; } ;
struct TYPE_8__ {int ino; scalar_t__ state; int /*<<< orphan*/  pino_nlink; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INO_STATE_CHECKEDABSENT ; 
 scalar_t__ INO_STATE_CHECKING ; 
 int /*<<< orphan*/  INO_STATE_PRESENT ; 
 scalar_t__ INO_STATE_READING ; 
 int /*<<< orphan*/  JFFS2_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  JFFS2_NOTICE (char*) ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,...) ; 
 int /*<<< orphan*/  RB_ROOT ; 
#define  S_IFBLK 132 
#define  S_IFCHR 131 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int S_IXUGO ; 
 void* cpu_to_je16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_je32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_jemode (int) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct jffs2_raw_inode*,int) ; 
 int /*<<< orphan*/  dbg_readinode (char*,...) ; 
 TYPE_4__* frag_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_next (TYPE_4__*) ; 
 size_t je32_to_cpu (void*) ; 
 int jemode_to_cpu (int /*<<< orphan*/ ) ; 
 int jffs2_build_inode_fragtree (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_readinode_info*) ; 
 int /*<<< orphan*/  jffs2_dbg_fragtree_paranoia_check_nolock (struct jffs2_inode_info*) ; 
 int /*<<< orphan*/  jffs2_do_clear_inode (struct jffs2_sb_info*,struct jffs2_inode_info*) ; 
 int jffs2_flash_read (struct jffs2_sb_info*,int,size_t,size_t*,char*) ; 
 int /*<<< orphan*/  jffs2_free_full_dnode (TYPE_5__*) ; 
 int /*<<< orphan*/  jffs2_free_node_frag (TYPE_4__*) ; 
 int /*<<< orphan*/  jffs2_free_tmp_dnode_info (TYPE_2__*) ; 
 int /*<<< orphan*/  jffs2_free_tmp_dnode_info_list (int /*<<< orphan*/ *) ; 
 int jffs2_get_inode_nodes (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_readinode_info*) ; 
 int /*<<< orphan*/  jffs2_kill_tn (struct jffs2_sb_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  jffs2_set_inocache_state (struct jffs2_sb_info*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jffs2_truncate_fragtree (struct jffs2_sb_info*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct jffs2_readinode_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ref_offset (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int jffs2_do_read_inode_internal(struct jffs2_sb_info *c,
					struct jffs2_inode_info *f,
					struct jffs2_raw_inode *latest_node)
{
	struct jffs2_readinode_info rii;
	uint32_t crc, new_size;
	size_t retlen;
	int ret;

	dbg_readinode("ino #%u pino/nlink is %d\n", f->inocache->ino,
		      f->inocache->pino_nlink);

	memset(&rii, 0, sizeof(rii));

	/* Grab all nodes relevant to this ino */
	ret = jffs2_get_inode_nodes(c, f, &rii);

	if (ret) {
		JFFS2_ERROR("cannot read nodes for ino %u, returned error is %d\n", f->inocache->ino, ret);
		if (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		return ret;
	}

	ret = jffs2_build_inode_fragtree(c, f, &rii);
	if (ret) {
		JFFS2_ERROR("Failed to build final fragtree for inode #%u: error %d\n",
			    f->inocache->ino, ret);
		if (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		jffs2_free_tmp_dnode_info_list(&rii.tn_root);
		/* FIXME: We could at least crc-check them all */
		if (rii.mdata_tn) {
			jffs2_free_full_dnode(rii.mdata_tn->fn);
			jffs2_free_tmp_dnode_info(rii.mdata_tn);
			rii.mdata_tn = NULL;
		}
		return ret;
	}

	if (rii.mdata_tn) {
		if (rii.mdata_tn->fn->raw == rii.latest_ref) {
			f->metadata = rii.mdata_tn->fn;
			jffs2_free_tmp_dnode_info(rii.mdata_tn);
		} else {
			jffs2_kill_tn(c, rii.mdata_tn);
		}
		rii.mdata_tn = NULL;
	}

	f->dents = rii.fds;

	jffs2_dbg_fragtree_paranoia_check_nolock(f);

	if (unlikely(!rii.latest_ref)) {
		/* No data nodes for this inode. */
		if (f->inocache->ino != 1) {
			JFFS2_WARNING("no data nodes found for ino #%u\n", f->inocache->ino);
			if (!rii.fds) {
				if (f->inocache->state == INO_STATE_READING)
					jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
				return -EIO;
			}
			JFFS2_NOTICE("but it has children so we fake some modes for it\n");
		}
		latest_node->mode = cpu_to_jemode(S_IFDIR|S_IRUGO|S_IWUSR|S_IXUGO);
		latest_node->version = cpu_to_je32(0);
		latest_node->atime = latest_node->ctime = latest_node->mtime = cpu_to_je32(0);
		latest_node->isize = cpu_to_je32(0);
		latest_node->gid = cpu_to_je16(0);
		latest_node->uid = cpu_to_je16(0);
		if (f->inocache->state == INO_STATE_READING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_PRESENT);
		return 0;
	}

	ret = jffs2_flash_read(c, ref_offset(rii.latest_ref), sizeof(*latest_node), &retlen, (void *)latest_node);
	if (ret || retlen != sizeof(*latest_node)) {
		JFFS2_ERROR("failed to read from flash: error %d, %zd of %zd bytes read\n",
			ret, retlen, sizeof(*latest_node));
		/* FIXME: If this fails, there seems to be a memory leak. Find it. */
		mutex_unlock(&f->sem);
		jffs2_do_clear_inode(c, f);
		return ret?ret:-EIO;
	}

	crc = crc32(0, latest_node, sizeof(*latest_node)-8);
	if (crc != je32_to_cpu(latest_node->node_crc)) {
		JFFS2_ERROR("CRC failed for read_inode of inode %u at physical location 0x%x\n",
			f->inocache->ino, ref_offset(rii.latest_ref));
		mutex_unlock(&f->sem);
		jffs2_do_clear_inode(c, f);
		return -EIO;
	}

	switch(jemode_to_cpu(latest_node->mode) & S_IFMT) {
	case S_IFDIR:
		if (rii.mctime_ver > je32_to_cpu(latest_node->version)) {
			/* The times in the latest_node are actually older than
			   mctime in the latest dirent. Cheat. */
			latest_node->ctime = latest_node->mtime = cpu_to_je32(rii.latest_mctime);
		}
		break;


	case S_IFREG:
		/* If it was a regular file, truncate it to the latest node's isize */
		new_size = jffs2_truncate_fragtree(c, &f->fragtree, je32_to_cpu(latest_node->isize));
		if (new_size != je32_to_cpu(latest_node->isize)) {
			JFFS2_WARNING("Truncating ino #%u to %d bytes failed because it only had %d bytes to start with!\n",
				      f->inocache->ino, je32_to_cpu(latest_node->isize), new_size);
			latest_node->isize = cpu_to_je32(new_size);
		}
		break;

	case S_IFLNK:
		/* Hack to work around broken isize in old symlink code.
		   Remove this when dwmw2 comes to his senses and stops
		   symlinks from being an entirely gratuitous special
		   case. */
		if (!je32_to_cpu(latest_node->isize))
			latest_node->isize = latest_node->dsize;

		if (f->inocache->state != INO_STATE_CHECKING) {
			/* Symlink's inode data is the target path. Read it and
			 * keep in RAM to facilitate quick follow symlink
			 * operation. */
			f->target = kmalloc(je32_to_cpu(latest_node->csize) + 1, GFP_KERNEL);
			if (!f->target) {
				JFFS2_ERROR("can't allocate %d bytes of memory for the symlink target path cache\n", je32_to_cpu(latest_node->csize));
				mutex_unlock(&f->sem);
				jffs2_do_clear_inode(c, f);
				return -ENOMEM;
			}

			ret = jffs2_flash_read(c, ref_offset(rii.latest_ref) + sizeof(*latest_node),
						je32_to_cpu(latest_node->csize), &retlen, (char *)f->target);

			if (ret  || retlen != je32_to_cpu(latest_node->csize)) {
				if (retlen != je32_to_cpu(latest_node->csize))
					ret = -EIO;
				kfree(f->target);
				f->target = NULL;
				mutex_unlock(&f->sem);
				jffs2_do_clear_inode(c, f);
				return -ret;
			}

			f->target[je32_to_cpu(latest_node->csize)] = '\0';
			dbg_readinode("symlink's target '%s' cached\n", f->target);
		}

		/* fall through... */

	case S_IFBLK:
	case S_IFCHR:
		/* Certain inode types should have only one data node, and it's
		   kept as the metadata node */
		if (f->metadata) {
			JFFS2_ERROR("Argh. Special inode #%u with mode 0%o had metadata node\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			mutex_unlock(&f->sem);
			jffs2_do_clear_inode(c, f);
			return -EIO;
		}
		if (!frag_first(&f->fragtree)) {
			JFFS2_ERROR("Argh. Special inode #%u with mode 0%o has no fragments\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			mutex_unlock(&f->sem);
			jffs2_do_clear_inode(c, f);
			return -EIO;
		}
		/* ASSERT: f->fraglist != NULL */
		if (frag_next(frag_first(&f->fragtree))) {
			JFFS2_ERROR("Argh. Special inode #%u with mode 0x%x had more than one node\n",
			       f->inocache->ino, jemode_to_cpu(latest_node->mode));
			/* FIXME: Deal with it - check crc32, check for duplicate node, check times and discard the older one */
			mutex_unlock(&f->sem);
			jffs2_do_clear_inode(c, f);
			return -EIO;
		}
		/* OK. We're happy */
		f->metadata = frag_first(&f->fragtree)->node;
		jffs2_free_node_frag(frag_first(&f->fragtree));
		f->fragtree = RB_ROOT;
		break;
	}
	if (f->inocache->state == INO_STATE_READING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_PRESENT);

	return 0;
}