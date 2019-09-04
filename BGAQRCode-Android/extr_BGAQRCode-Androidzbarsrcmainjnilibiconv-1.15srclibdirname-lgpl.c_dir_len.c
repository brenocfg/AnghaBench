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
 scalar_t__ DOUBLE_SLASH_IS_DISTINCT_ROOT ; 
 scalar_t__ FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE ; 
 size_t FILE_SYSTEM_PREFIX_LEN (char const*) ; 
 scalar_t__ ISSLASH (char const) ; 
 char const* last_component (char const*) ; 

size_t
dir_len (char const *file)
{
  size_t prefix_length = FILE_SYSTEM_PREFIX_LEN (file);
  size_t length;

  /* Advance prefix_length beyond important leading slashes.  */
  prefix_length += (prefix_length != 0
                    ? (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
                       && ISSLASH (file[prefix_length]))
                    : (ISSLASH (file[0])
                       ? ((DOUBLE_SLASH_IS_DISTINCT_ROOT
                           && ISSLASH (file[1]) && ! ISSLASH (file[2])
                           ? 2 : 1))
                       : 0));

  /* Strip the basename and any redundant slashes before it.  */
  for (length = last_component (file) - file;
       prefix_length < length; length--)
    if (! ISSLASH (file[length - 1]))
      break;
  return length;
}