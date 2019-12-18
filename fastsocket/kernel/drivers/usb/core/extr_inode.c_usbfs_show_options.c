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
struct vfsmount {int dummy; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ USBFS_DEFAULT_BUSMODE ; 
 scalar_t__ USBFS_DEFAULT_DEVMODE ; 
 scalar_t__ USBFS_DEFAULT_LISTMODE ; 
 scalar_t__ busgid ; 
 scalar_t__ busmode ; 
 scalar_t__ busuid ; 
 scalar_t__ devgid ; 
 scalar_t__ devmode ; 
 scalar_t__ devuid ; 
 scalar_t__ listgid ; 
 scalar_t__ listmode ; 
 scalar_t__ listuid ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static int usbfs_show_options(struct seq_file *seq, struct vfsmount *mnt)
{
	if (devuid != 0)
		seq_printf(seq, ",devuid=%u", devuid);
	if (devgid != 0)
		seq_printf(seq, ",devgid=%u", devgid);
	if (devmode != USBFS_DEFAULT_DEVMODE)
		seq_printf(seq, ",devmode=%o", devmode);
	if (busuid != 0)
		seq_printf(seq, ",busuid=%u", busuid);
	if (busgid != 0)
		seq_printf(seq, ",busgid=%u", busgid);
	if (busmode != USBFS_DEFAULT_BUSMODE)
		seq_printf(seq, ",busmode=%o", busmode);
	if (listuid != 0)
		seq_printf(seq, ",listuid=%u", listuid);
	if (listgid != 0)
		seq_printf(seq, ",listgid=%u", listgid);
	if (listmode != USBFS_DEFAULT_LISTMODE)
		seq_printf(seq, ",listmode=%o", listmode);

	return 0;
}