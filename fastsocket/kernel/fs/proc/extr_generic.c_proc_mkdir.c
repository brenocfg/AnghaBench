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
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct proc_dir_entry* proc_mkdir_mode (char const*,int,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_mkdir(const char *name,
		struct proc_dir_entry *parent)
{
	return proc_mkdir_mode(name, S_IRUGO | S_IXUGO, parent);
}