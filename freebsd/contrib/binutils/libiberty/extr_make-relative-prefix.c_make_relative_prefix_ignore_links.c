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

/* Variables and functions */
 char* make_relative_prefix_1 (char const*,char const*,char const*,int /*<<< orphan*/ ) ; 

char *
make_relative_prefix_ignore_links (const char *progname,
				   const char *bin_prefix,
				   const char *prefix)
{
  return make_relative_prefix_1 (progname, bin_prefix, prefix, 0);
}