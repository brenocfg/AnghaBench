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

/* Variables and functions */
 int gss_pipe_open (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gss_pipe_open_v0(struct inode *inode)
{
	return gss_pipe_open(inode, 0);
}