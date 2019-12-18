#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nw_info_struct {int attributes; int /*<<< orphan*/  dataStreamSize; } ;
struct TYPE_3__ {int dir_mode; int file_mode; int flags; } ;
struct ncp_server {TYPE_1__ m; } ;
struct ncp_entry_info {struct nw_info_struct i; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCPI_KLUDGE_SYMLINK ; 
 int /*<<< orphan*/  NCP_BLOCK_SIZE ; 
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  NCP_MAX_SYMLINK_SIZE ; 
 int NCP_MOUNT_EXTRAS ; 
 int NCP_MOUNT_SYMLINKS ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 int aDIR ; 
#define  aHIDDEN 129 
 int aRONLY ; 
 int aSHARED ; 
#define  aSYSTEM 128 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ncp_update_attrs(struct inode *inode, struct ncp_entry_info *nwinfo)
{
	struct nw_info_struct *nwi = &nwinfo->i;
	struct ncp_server *server = NCP_SERVER(inode);

	if (nwi->attributes & aDIR) {
		inode->i_mode = server->m.dir_mode;
		/* for directories dataStreamSize seems to be some
		   Object ID ??? */
		inode->i_size = NCP_BLOCK_SIZE;
	} else {
		inode->i_mode = server->m.file_mode;
		inode->i_size = le32_to_cpu(nwi->dataStreamSize);
#ifdef CONFIG_NCPFS_EXTRAS
		if ((server->m.flags & (NCP_MOUNT_EXTRAS|NCP_MOUNT_SYMLINKS)) 
		 && (nwi->attributes & aSHARED)) {
			switch (nwi->attributes & (aHIDDEN|aSYSTEM)) {
				case aHIDDEN:
					if (server->m.flags & NCP_MOUNT_SYMLINKS) {
						if (/* (inode->i_size >= NCP_MIN_SYMLINK_SIZE)
						 && */ (inode->i_size <= NCP_MAX_SYMLINK_SIZE)) {
							inode->i_mode = (inode->i_mode & ~S_IFMT) | S_IFLNK;
							NCP_FINFO(inode)->flags |= NCPI_KLUDGE_SYMLINK;
							break;
						}
					}
					/* FALLTHROUGH */
				case 0:
					if (server->m.flags & NCP_MOUNT_EXTRAS)
						inode->i_mode |= S_IRUGO;
					break;
				case aSYSTEM:
					if (server->m.flags & NCP_MOUNT_EXTRAS)
						inode->i_mode |= (inode->i_mode >> 2) & S_IXUGO;
					break;
				/* case aSYSTEM|aHIDDEN: */
				default:
					/* reserved combination */
					break;
			}
		}
#endif
	}
	if (nwi->attributes & aRONLY) inode->i_mode &= ~S_IWUGO;
}