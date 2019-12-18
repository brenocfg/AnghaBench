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
struct inode {int /*<<< orphan*/ * i_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pipe_info (int /*<<< orphan*/ *) ; 

void free_pipe_info(struct inode *inode)
{
	__free_pipe_info(inode->i_pipe);
	inode->i_pipe = NULL;
}