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
struct inode {int /*<<< orphan*/ * i_fop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ns_file_operations ; 

bool proc_ns_inode(struct inode *inode)
{
	return inode->i_fop == &ns_file_operations;
}