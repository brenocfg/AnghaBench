#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* no_formal_ino; void* no_addr; } ;
struct TYPE_7__ {void* no_formal_ino; void* no_addr; } ;
struct gfs2_sb_host {int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_locktable; int /*<<< orphan*/  sb_lockproto; TYPE_4__ sb_root_dir; TYPE_2__ sb_master_dir; void* sb_bsize_shift; void* sb_bsize; void* sb_multihost_format; void* sb_fs_format; void* sb_format; void* sb_type; void* sb_magic; } ;
struct TYPE_10__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mh_format; int /*<<< orphan*/  mh_type; int /*<<< orphan*/  mh_magic; } ;
struct gfs2_sb {int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_locktable; int /*<<< orphan*/  sb_lockproto; TYPE_5__ sb_root_dir; TYPE_3__ sb_master_dir; int /*<<< orphan*/  sb_bsize_shift; int /*<<< orphan*/  sb_bsize; int /*<<< orphan*/  sb_multihost_format; int /*<<< orphan*/  sb_fs_format; TYPE_1__ sb_header; } ;

/* Variables and functions */
 int GFS2_LOCKNAME_LEN ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfs2_sb_in(struct gfs2_sb_host *sb, const void *buf)
{
	const struct gfs2_sb *str = buf;

	sb->sb_magic = be32_to_cpu(str->sb_header.mh_magic);
	sb->sb_type = be32_to_cpu(str->sb_header.mh_type);
	sb->sb_format = be32_to_cpu(str->sb_header.mh_format);
	sb->sb_fs_format = be32_to_cpu(str->sb_fs_format);
	sb->sb_multihost_format = be32_to_cpu(str->sb_multihost_format);
	sb->sb_bsize = be32_to_cpu(str->sb_bsize);
	sb->sb_bsize_shift = be32_to_cpu(str->sb_bsize_shift);
	sb->sb_master_dir.no_addr = be64_to_cpu(str->sb_master_dir.no_addr);
	sb->sb_master_dir.no_formal_ino = be64_to_cpu(str->sb_master_dir.no_formal_ino);
	sb->sb_root_dir.no_addr = be64_to_cpu(str->sb_root_dir.no_addr);
	sb->sb_root_dir.no_formal_ino = be64_to_cpu(str->sb_root_dir.no_formal_ino);

	memcpy(sb->sb_lockproto, str->sb_lockproto, GFS2_LOCKNAME_LEN);
	memcpy(sb->sb_locktable, str->sb_locktable, GFS2_LOCKNAME_LEN);
	memcpy(sb->sb_uuid, str->sb_uuid, 16);
}