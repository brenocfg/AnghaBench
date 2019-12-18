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
struct filename {char const* name; } ;

/* Variables and functions */
 int filename_lookup (int,struct filename*,unsigned int,struct nameidata*) ; 

__attribute__((used)) static int do_path_lookup(int dfd, const char *name,
				unsigned int flags, struct nameidata *nd)
{
	struct filename filename = { .name = name };

	return filename_lookup(dfd, &filename, flags, nd);
}