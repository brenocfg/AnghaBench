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
struct nfs4_file {int dummy; } ;

/* Variables and functions */
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  __nfs4_file_put_access (struct nfs4_file*,int) ; 

__attribute__((used)) static void nfs4_file_put_access(struct nfs4_file *fp, int oflag)
{
	if (oflag == O_RDWR) {
		__nfs4_file_put_access(fp, O_RDONLY);
		__nfs4_file_put_access(fp, O_WRONLY);
	} else
		__nfs4_file_put_access(fp, oflag);
}