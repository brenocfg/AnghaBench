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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  def_file ; 
 int /*<<< orphan*/  dll_name ; 
 char* lbasename (char const*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void
set_dll_name_from_def (const char * name)
{
  const char* image_basename = lbasename (name);
  if (image_basename != name)
    non_fatal (_("%s: Path components stripped from image name, '%s'."),
	      def_file, name);
  dll_name = xstrdup (image_basename);
}