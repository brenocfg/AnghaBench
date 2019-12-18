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
struct nfs4_file {struct file** fi_fds; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t O_RDONLY ; 
 size_t O_RDWR ; 
 size_t O_WRONLY ; 

__attribute__((used)) static inline struct file *find_any_file(struct nfs4_file *f)
{
	if (f->fi_fds[O_RDWR])
		return f->fi_fds[O_RDWR];
	else if (f->fi_fds[O_WRONLY])
		return f->fi_fds[O_WRONLY];
	else
		return f->fi_fds[O_RDONLY];
}