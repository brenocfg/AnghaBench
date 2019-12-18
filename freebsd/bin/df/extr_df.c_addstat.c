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
typedef  int uint64_t ;
struct statfs {int f_bsize; int f_blocks; int f_bfree; int f_bavail; scalar_t__ f_ffree; scalar_t__ f_files; } ;

/* Variables and functions */

__attribute__((used)) static void
addstat(struct statfs *totalfsp, struct statfs *statfsp)
{
	uint64_t bsize;

	bsize = statfsp->f_bsize / totalfsp->f_bsize;
	totalfsp->f_blocks += statfsp->f_blocks * bsize;
	totalfsp->f_bfree += statfsp->f_bfree * bsize;
	totalfsp->f_bavail += statfsp->f_bavail * bsize;
	totalfsp->f_files += statfsp->f_files;
	totalfsp->f_ffree += statfsp->f_ffree;
}