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
struct add_to_obstack_info {int first_time; int /*<<< orphan*/  ob; scalar_t__ check_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_SEPARATOR ; 
 int /*<<< orphan*/  is_directory (char*,int) ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void *
add_to_obstack (char *path, void *data)
{
  struct add_to_obstack_info *info = data;

  if (info->check_dir && !is_directory (path, false))
    return NULL;

  if (!info->first_time)
    obstack_1grow (info->ob, PATH_SEPARATOR);

  obstack_grow (info->ob, path, strlen (path));

  info->first_time = false;
  return NULL;
}