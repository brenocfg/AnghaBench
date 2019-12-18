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
struct seq_file {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;

/* Variables and functions */
 int CIFS_MOUNT_DIRECT_IO ; 
 int CIFS_MOUNT_STRICT_IO ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static void
cifs_show_cache_flavor(struct seq_file *s, struct cifs_sb_info *cifs_sb)
{
	seq_printf(s, ",cache=");

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_STRICT_IO)
		seq_printf(s, "strict");
	else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DIRECT_IO)
		seq_printf(s, "none");
	else
		seq_printf(s, "loose");
}