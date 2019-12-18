#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int i_mode; int i_uid; int i_gid; int i_nlink; TYPE_5__ i_ctime; TYPE_4__ i_mtime; TYPE_3__ i_atime; } ;
struct gfs2_inode {int i_diskflags; int i_entries; TYPE_6__ i_inode; int /*<<< orphan*/  i_eattr; int /*<<< orphan*/  i_depth; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_goal; int /*<<< orphan*/  i_no_formal_ino; int /*<<< orphan*/  i_no_addr; } ;
struct TYPE_9__ {void* no_formal_ino; void* no_addr; } ;
struct TYPE_8__ {void* mh_format; void* mh_type; void* mh_magic; } ;
struct gfs2_dinode {void* di_ctime_nsec; void* di_mtime_nsec; void* di_atime_nsec; void* di_eattr; void* di_entries; void* di_depth; void* di_payload_format; void* di_height; void* di_flags; void* di_generation; void* di_goal_data; void* di_goal_meta; void* di_ctime; void* di_mtime; void* di_atime; void* di_blocks; void* di_size; void* di_nlink; void* di_gid; void* di_uid; void* di_mode; TYPE_2__ di_num; TYPE_1__ di_header; } ;

/* Variables and functions */
 int GFS2_DIF_EXHASH ; 
 int GFS2_FORMAT_DE ; 
 int GFS2_FORMAT_DI ; 
 int GFS2_MAGIC ; 
 int GFS2_METATYPE_DI ; 
 scalar_t__ S_ISDIR (int) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_get_inode_blocks (TYPE_6__*) ; 
 int /*<<< orphan*/  i_size_read (TYPE_6__*) ; 

void gfs2_dinode_out(const struct gfs2_inode *ip, void *buf)
{
	struct gfs2_dinode *str = buf;

	str->di_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	str->di_header.mh_type = cpu_to_be32(GFS2_METATYPE_DI);
	str->di_header.mh_format = cpu_to_be32(GFS2_FORMAT_DI);
	str->di_num.no_addr = cpu_to_be64(ip->i_no_addr);
	str->di_num.no_formal_ino = cpu_to_be64(ip->i_no_formal_ino);
	str->di_mode = cpu_to_be32(ip->i_inode.i_mode);
	str->di_uid = cpu_to_be32(ip->i_inode.i_uid);
	str->di_gid = cpu_to_be32(ip->i_inode.i_gid);
	str->di_nlink = cpu_to_be32(ip->i_inode.i_nlink);
	str->di_size = cpu_to_be64(i_size_read(&ip->i_inode));
	str->di_blocks = cpu_to_be64(gfs2_get_inode_blocks(&ip->i_inode));
	str->di_atime = cpu_to_be64(ip->i_inode.i_atime.tv_sec);
	str->di_mtime = cpu_to_be64(ip->i_inode.i_mtime.tv_sec);
	str->di_ctime = cpu_to_be64(ip->i_inode.i_ctime.tv_sec);

	str->di_goal_meta = cpu_to_be64(ip->i_goal);
	str->di_goal_data = cpu_to_be64(ip->i_goal);
	str->di_generation = cpu_to_be64(ip->i_generation);

	str->di_flags = cpu_to_be32(ip->i_diskflags);
	str->di_height = cpu_to_be16(ip->i_height);
	str->di_payload_format = cpu_to_be32(S_ISDIR(ip->i_inode.i_mode) &&
					     !(ip->i_diskflags & GFS2_DIF_EXHASH) ?
					     GFS2_FORMAT_DE : 0);
	str->di_depth = cpu_to_be16(ip->i_depth);
	str->di_entries = cpu_to_be32(ip->i_entries);

	str->di_eattr = cpu_to_be64(ip->i_eattr);
	str->di_atime_nsec = cpu_to_be32(ip->i_inode.i_atime.tv_nsec);
	str->di_mtime_nsec = cpu_to_be32(ip->i_inode.i_mtime.tv_nsec);
	str->di_ctime_nsec = cpu_to_be32(ip->i_inode.i_ctime.tv_nsec);
}