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
struct inode {int dummy; } ;
struct file {int f_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  default_hard; int /*<<< orphan*/  default_soft; int /*<<< orphan*/  (* sq_open ) (int) ;} ;
struct TYPE_4__ {int minDev; TYPE_1__ mach; int /*<<< orphan*/  hard; int /*<<< orphan*/  dsp; int /*<<< orphan*/  soft; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_MU_LAW ; 
 int ENODEV ; 
 int ENXIO ; 
 int FMODE_READ ; 
 int SND_DEV_AUDIO ; 
 TYPE_2__ dmasound ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ shared_resource_owner ; 
 int /*<<< orphan*/  sound_set_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sound_set_speed (int) ; 
 int /*<<< orphan*/  sound_set_stereo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int write_sq_open (struct file*) ; 

__attribute__((used)) static int sq_open(struct inode *inode, struct file *file)
{
	int rc;

	if (!try_module_get(dmasound.mach.owner))
		return -ENODEV;

	rc = write_sq_open(file); /* checks the f_mode */
	if (rc)
		goto out;
	if (file->f_mode & FMODE_READ) {
		/* TODO: if O_RDWR, release any resources grabbed by write part */
		rc = -ENXIO ; /* I think this is what is required by open(2) */
		goto out;
	}

	if (dmasound.mach.sq_open)
	    dmasound.mach.sq_open(file->f_mode);

	/* CHECK whether this is sensible - in the case that dsp0 could be opened
	  O_RDONLY and dsp1 could be opened O_WRONLY
	*/

	dmasound.minDev = iminor(inode) & 0x0f;

	/* OK. - we should make some attempt at consistency. At least the H'ware
	   options should be set with a valid mode.  We will make it that the LL
	   driver must supply defaults for hard & soft params.
	*/

	if (shared_resource_owner == 0) {
		/* you can make this AFMT_U8/mono/8K if you want to mimic old
		   OSS behaviour - while we still have soft translations ;-) */
		dmasound.soft = dmasound.mach.default_soft ;
		dmasound.dsp = dmasound.mach.default_soft ;
		dmasound.hard = dmasound.mach.default_hard ;
	}

#ifndef DMASOUND_STRICT_OSS_COMPLIANCE
	/* none of the current LL drivers can actually do this "native" at the moment
	   OSS does not really require us to supply /dev/audio if we can't do it.
	*/
	if (dmasound.minDev == SND_DEV_AUDIO) {
		sound_set_speed(8000);
		sound_set_stereo(0);
		sound_set_format(AFMT_MU_LAW);
	}
#endif

	return 0;
 out:
	module_put(dmasound.mach.owner);
	return rc;
}