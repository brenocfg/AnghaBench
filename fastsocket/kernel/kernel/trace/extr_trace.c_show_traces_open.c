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
 int ENODEV ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_traces_seq_ops ; 
 scalar_t__ tracing_disabled ; 

__attribute__((used)) static int show_traces_open(struct inode *inode, struct file *file)
{
	if (tracing_disabled)
		return -ENODEV;

	return seq_open(file, &show_traces_seq_ops);
}