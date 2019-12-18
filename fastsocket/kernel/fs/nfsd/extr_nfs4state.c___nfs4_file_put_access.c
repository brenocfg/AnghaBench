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
struct nfs4_file {int /*<<< orphan*/ * fi_access; } ;

/* Variables and functions */
 int O_RDWR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_file_put_fd (struct nfs4_file*,int) ; 

__attribute__((used)) static void __nfs4_file_put_access(struct nfs4_file *fp, int oflag)
{
	if (atomic_dec_and_test(&fp->fi_access[oflag])) {
		nfs4_file_put_fd(fp, oflag);
		if (atomic_read(&fp->fi_access[1 - oflag]) == 0)
			nfs4_file_put_fd(fp, O_RDWR);
	}
}