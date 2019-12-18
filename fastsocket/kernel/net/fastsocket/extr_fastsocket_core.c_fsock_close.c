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
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,struct inode*,struct file*) ; 
 int fsocket_filp_close (struct file*) ; 

__attribute__((used)) static inline int fsock_close(struct inode *i_node, struct file *file)
{
	DPRINTK(DEBUG, "Enter fsock_close, inode(%p) file(%p)\n", i_node, file);

	return fsocket_filp_close(file);
}