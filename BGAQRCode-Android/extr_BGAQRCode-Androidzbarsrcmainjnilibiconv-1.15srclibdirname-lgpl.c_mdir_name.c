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
 scalar_t__ FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE ; 
 size_t FILE_SYSTEM_PREFIX_LEN (char const*) ; 
 int /*<<< orphan*/  ISSLASH (char const) ; 
 size_t dir_len (char const*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

char *
mdir_name (char const *file)
{
  size_t length = dir_len (file);
  bool append_dot = (length == 0
                     || (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
                         && length == FILE_SYSTEM_PREFIX_LEN (file)
                         && file[2] != '\0' && ! ISSLASH (file[2])));
  char *dir = malloc (length + append_dot + 1);
  if (!dir)
    return NULL;
  memcpy (dir, file, length);
  if (append_dot)
    dir[length++] = '.';
  dir[length] = '\0';
  return dir;
}