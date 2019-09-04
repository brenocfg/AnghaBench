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
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  fp_allocfn_t ;

/* Variables and functions */
 int falloc_withalloc_locked (int /*<<< orphan*/ ,struct fileproc**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

int
falloc_withalloc(proc_t p, struct fileproc **resultfp, int *resultfd,
    vfs_context_t ctx, fp_allocfn_t fp_zalloc, void *arg)
{
	int error;

	proc_fdlock(p);
	error = falloc_withalloc_locked(p,
	    resultfp, resultfd, ctx, fp_zalloc, arg, 1);
	proc_fdunlock(p);

	return (error);
}