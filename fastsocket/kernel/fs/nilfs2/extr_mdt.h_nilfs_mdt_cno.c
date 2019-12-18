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
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_4__ {TYPE_1__* mi_nilfs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ns_cno; } ;

/* Variables and functions */
 TYPE_2__* NILFS_MDT (struct inode*) ; 

__attribute__((used)) static inline __u64 nilfs_mdt_cno(struct inode *inode)
{
	return NILFS_MDT(inode)->mi_nilfs->ns_cno;
}