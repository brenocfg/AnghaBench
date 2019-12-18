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
struct nfs4_file {int /*<<< orphan*/ ** fi_fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_file_put_fd(struct nfs4_file *fp, int oflag)
{
	if (fp->fi_fds[oflag]) {
		fput(fp->fi_fds[oflag]);
		fp->fi_fds[oflag] = NULL;
	}
}