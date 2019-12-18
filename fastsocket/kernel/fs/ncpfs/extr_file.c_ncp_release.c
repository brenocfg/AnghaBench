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
 int /*<<< orphan*/  DPRINTK (char*) ; 
 scalar_t__ ncp_make_closed (struct inode*) ; 

__attribute__((used)) static int ncp_release(struct inode *inode, struct file *file) {
	if (ncp_make_closed(inode)) {
		DPRINTK("ncp_release: failed to close\n");
	}
	return 0;
}