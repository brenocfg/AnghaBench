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
struct nfs4_file {int /*<<< orphan*/ * fi_access; scalar_t__* fi_fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t O_RDWR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __nfs4_file_get_access(struct nfs4_file *fp, int oflag)
{
	BUG_ON(!(fp->fi_fds[oflag] || fp->fi_fds[O_RDWR]));
	atomic_inc(&fp->fi_access[oflag]);
}