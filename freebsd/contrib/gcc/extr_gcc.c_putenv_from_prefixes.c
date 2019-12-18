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
struct path_prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_search_list (struct path_prefix const*,char const*,int,int) ; 
 int /*<<< orphan*/  putenv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
putenv_from_prefixes (const struct path_prefix *paths, const char *env_var,
		      bool do_multi)
{
  putenv (build_search_list (paths, env_var, true, do_multi));
}