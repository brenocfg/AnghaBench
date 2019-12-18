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
struct nameidata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int do_path_lookup (int /*<<< orphan*/ ,char const*,unsigned int,struct nameidata*) ; 

int path_lookup(const char *name, unsigned int flags,
			struct nameidata *nd)
{
	return do_path_lookup(AT_FDCWD, name, flags, nd);
}