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
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct kstat {TYPE_1__ ctime; } ;
struct inode {int /*<<< orphan*/  i_version; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_I_VERSION (struct inode*) ; 
 int /*<<< orphan*/  write32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write64 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_change(__be32 **p, struct kstat *stat, struct inode *inode)
{
	if (IS_I_VERSION(inode)) {
		write64(p, inode->i_version);
	} else {
		write32(p, stat->ctime.tv_sec);
		write32(p, stat->ctime.tv_nsec);
	}
}