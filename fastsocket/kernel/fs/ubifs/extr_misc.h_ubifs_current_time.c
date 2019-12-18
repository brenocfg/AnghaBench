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
struct timespec {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {scalar_t__ s_time_gran; } ;

/* Variables and functions */
 struct timespec CURRENT_TIME_SEC ; 
 scalar_t__ NSEC_PER_SEC ; 
 struct timespec current_fs_time (TYPE_1__*) ; 

__attribute__((used)) static inline struct timespec ubifs_current_time(struct inode *inode)
{
	return (inode->i_sb->s_time_gran < NSEC_PER_SEC) ?
		current_fs_time(inode->i_sb) : CURRENT_TIME_SEC;
}