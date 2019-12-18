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
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char const*) ; 
 int /*<<< orphan*/  add_prefix (struct path_prefix*,char const*,char const*,int,int,int) ; 
 char* concat (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 scalar_t__ target_sysroot_suffix ; 
 scalar_t__ target_system_root ; 

__attribute__((used)) static void
add_sysrooted_prefix (struct path_prefix *pprefix, const char *prefix,
		      const char *component,
		      /* enum prefix_priority */ int priority,
		      int require_machine_suffix, int os_multilib)
{
  if (!IS_ABSOLUTE_PATH (prefix))
    fatal ("system path '%s' is not absolute", prefix);

  if (target_system_root)
    {
      if (target_sysroot_suffix)
	  prefix = concat (target_sysroot_suffix, prefix, NULL);
      prefix = concat (target_system_root, prefix, NULL);

      /* We have to override this because GCC's notion of sysroot
	 moves along with GCC.  */
      component = "GCC";
    }

  add_prefix (pprefix, prefix, component, priority,
	      require_machine_suffix, os_multilib);
}