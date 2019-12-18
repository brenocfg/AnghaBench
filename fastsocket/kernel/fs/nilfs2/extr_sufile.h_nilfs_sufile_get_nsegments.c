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
struct TYPE_4__ {TYPE_1__* mi_nilfs; } ;
struct TYPE_3__ {unsigned long ns_nsegments; } ;

/* Variables and functions */
 TYPE_2__* NILFS_MDT (struct inode*) ; 

__attribute__((used)) static inline unsigned long nilfs_sufile_get_nsegments(struct inode *sufile)
{
	return NILFS_MDT(sufile)->mi_nilfs->ns_nsegments;
}