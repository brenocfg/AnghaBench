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
struct knote {int dummy; } ;
struct kevent_internal_s {int dummy; } ;
struct fileproc {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
noop_kqfilter(struct fileproc *fp, struct knote *kn,
		struct kevent_internal_s *kev, vfs_context_t ctx)
{
#pragma unused(fp, kn, kev, ctx)
	return (ENXIO);
}