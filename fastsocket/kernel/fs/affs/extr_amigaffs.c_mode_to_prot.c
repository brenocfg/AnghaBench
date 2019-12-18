#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int i_mode; } ;
typedef  int mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_protect; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  FIBF_GRP_EXECUTE ; 
 int /*<<< orphan*/  FIBF_GRP_READ ; 
 int /*<<< orphan*/  FIBF_GRP_WRITE ; 
 int /*<<< orphan*/  FIBF_NOEXECUTE ; 
 int /*<<< orphan*/  FIBF_NOREAD ; 
 int /*<<< orphan*/  FIBF_NOWRITE ; 
 int /*<<< orphan*/  FIBF_OTR_EXECUTE ; 
 int /*<<< orphan*/  FIBF_OTR_READ ; 
 int /*<<< orphan*/  FIBF_OTR_WRITE ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 

void
mode_to_prot(struct inode *inode)
{
	u32 prot = AFFS_I(inode)->i_protect;
	mode_t mode = inode->i_mode;

	if (!(mode & S_IXUSR))
		prot |= FIBF_NOEXECUTE;
	if (!(mode & S_IRUSR))
		prot |= FIBF_NOREAD;
	if (!(mode & S_IWUSR))
		prot |= FIBF_NOWRITE;
	if (mode & S_IXGRP)
		prot |= FIBF_GRP_EXECUTE;
	if (mode & S_IRGRP)
		prot |= FIBF_GRP_READ;
	if (mode & S_IWGRP)
		prot |= FIBF_GRP_WRITE;
	if (mode & S_IXOTH)
		prot |= FIBF_OTR_EXECUTE;
	if (mode & S_IROTH)
		prot |= FIBF_OTR_READ;
	if (mode & S_IWOTH)
		prot |= FIBF_OTR_WRITE;

	AFFS_I(inode)->i_protect = prot;
}