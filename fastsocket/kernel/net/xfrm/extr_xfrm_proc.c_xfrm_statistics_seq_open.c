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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int single_open_net (struct inode*,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_statistics_seq_show ; 

__attribute__((used)) static int xfrm_statistics_seq_open(struct inode *inode, struct file *file)
{
	return single_open_net(inode, file, xfrm_statistics_seq_show);
}