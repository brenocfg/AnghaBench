#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vnop_readdir_args {int a_flags; struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct uio {int uio_offset; } ;
struct dirent {int d_namlen; int d_reclen; int /*<<< orphan*/  d_name; void* d_type; int /*<<< orphan*/  d_fileno; } ;
struct TYPE_10__ {TYPE_1__* parent; TYPE_6__* dirlist; } ;
struct TYPE_11__ {TYPE_2__ Dir; } ;
struct TYPE_13__ {scalar_t__ dn_type; int /*<<< orphan*/  dn_ino; TYPE_3__ dn_typeinfo; } ;
typedef  TYPE_5__ devnode_t ;
struct TYPE_14__ {char* de_name; struct TYPE_14__* de_next; TYPE_4__* de_dnp; } ;
typedef  TYPE_6__ devdirent_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ino; } ;
struct TYPE_9__ {int /*<<< orphan*/  dn_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int /*<<< orphan*/  DEVFS_UPDATE_ACCESS ; 
 int /*<<< orphan*/  DEVMAXNAMESIZE ; 
#define  DEV_BDEV 131 
#define  DEV_CDEV 130 
#define  DEV_DIR 129 
#define  DEV_SLNK 128 
 void* DT_BLK ; 
 void* DT_CHR ; 
 void* DT_DIR ; 
 void* DT_LNK ; 
 void* DT_UNKNOWN ; 
 int EINVAL ; 
 int ENOTDIR ; 
 int MAXNAMLEN ; 
 int VNODE_READDIR_EXTENDED ; 
 int VNODE_READDIR_REQSEEKOFF ; 
 TYPE_5__* VTODN (struct vnode*) ; 
 int /*<<< orphan*/  devfs_consider_time_update (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int uio_resid (struct uio*) ; 
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
devfs_readdir(struct vnop_readdir_args *ap)
        /*struct vnop_readdir_args {
                struct vnode *a_vp;
                struct uio *a_uio;
		int a_flags;
		int *a_eofflag;
		int *a_numdirent;
		vfs_context_t a_context;
        } */
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct dirent dirent;
	devnode_t * dir_node;
	devdirent_t *	name_node;
	const char *name;
	int error = 0;
	int reclen;
	int nodenumber;
	int	startpos,pos;

	if (ap->a_flags & (VNODE_READDIR_EXTENDED | VNODE_READDIR_REQSEEKOFF))
		return (EINVAL);

	/*  set up refs to dir */
	dir_node = VTODN(vp);
	if (dir_node->dn_type != DEV_DIR)
		return(ENOTDIR);
	pos = 0;
	startpos = uio->uio_offset;

	DEVFS_LOCK();

	name_node = dir_node->dn_typeinfo.Dir.dirlist;
	nodenumber = 0;

	while ((name_node || (nodenumber < 2)) && (uio_resid(uio) > 0))
	{
		switch(nodenumber)
		{
		case	0:
			dirent.d_fileno = dir_node->dn_ino;
			name = ".";
			dirent.d_namlen = 1;
			dirent.d_type = DT_DIR;
			break;
		case	1:
			if(dir_node->dn_typeinfo.Dir.parent)
				dirent.d_fileno = dir_node->dn_typeinfo.Dir.parent->dn_ino;
			else
				dirent.d_fileno = dir_node->dn_ino;
			name = "..";
			dirent.d_namlen = 2;
			dirent.d_type = DT_DIR;
			break;
		default:
			dirent.d_fileno = name_node->de_dnp->dn_ino;
			dirent.d_namlen = strlen(name_node->de_name);
			name = name_node->de_name;
			switch(name_node->de_dnp->dn_type) {
			case DEV_BDEV:
				dirent.d_type = DT_BLK;
				break;
			case DEV_CDEV:
				dirent.d_type = DT_CHR;
				break;
			case DEV_DIR:
				dirent.d_type = DT_DIR;
				break;
			case DEV_SLNK:
				dirent.d_type = DT_LNK;
				break;
			default:
				dirent.d_type = DT_UNKNOWN;
			}
		}
#define	GENERIC_DIRSIZ(dp) \
    ((sizeof (struct dirent) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))

		reclen = dirent.d_reclen = GENERIC_DIRSIZ(&dirent);

		if(pos >= startpos)	/* made it to the offset yet? */
		{
			if (uio_resid(uio) < reclen) /* will it fit? */
				break;
			strlcpy(dirent.d_name, name, DEVMAXNAMESIZE);
			if ((error = uiomove ((caddr_t)&dirent,
					dirent.d_reclen, uio)) != 0)
				break;
		}
		pos += reclen;
		if((nodenumber >1) && name_node)
			name_node = name_node->de_next;
		nodenumber++;
	}
	DEVFS_UNLOCK();
	uio->uio_offset = pos;

	devfs_consider_time_update(dir_node, DEVFS_UPDATE_ACCESS);

	return (error);
}