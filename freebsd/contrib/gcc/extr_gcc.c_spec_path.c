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
struct spec_path_info {scalar_t__ append_len; char* option; scalar_t__ separate_options; int /*<<< orphan*/  append; scalar_t__ omit_relative; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 int /*<<< orphan*/  do_spec_1 (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_directory (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void *
spec_path (char *path, void *data)
{
  struct spec_path_info *info = data;
  size_t len = 0;
  char save = 0;

  if (info->omit_relative && !IS_ABSOLUTE_PATH (path))
    return NULL;

  if (info->append_len != 0)
    {
      len = strlen (path);
      memcpy (path + len, info->append, info->append_len + 1);
    }

  if (!is_directory (path, true))
    return NULL;

  do_spec_1 (info->option, 1, NULL);
  if (info->separate_options)
    do_spec_1 (" ", 0, NULL);

  if (info->append_len == 0)
    {
      len = strlen (path);
      save = path[len - 1];
      if (IS_DIR_SEPARATOR (path[len - 1]))
	path[len - 1] = '\0';
    }

  do_spec_1 (path, 1, NULL);
  do_spec_1 (" ", 0, NULL);

  /* Must not damage the original path.  */
  if (info->append_len == 0)
    path[len - 1] = save;

  return NULL;
}