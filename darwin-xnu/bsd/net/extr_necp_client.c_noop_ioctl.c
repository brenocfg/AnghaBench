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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct fileproc {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOTTY ; 

__attribute__((used)) static int
noop_ioctl(struct fileproc *fp, unsigned long com, caddr_t data,
		   vfs_context_t ctx)
{
#pragma unused(fp, com, data, ctx)
	return (ENOTTY);
}