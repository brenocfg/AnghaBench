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
 size_t strlen (char const*) ; 

size_t
base_len (char const *name)
{
  size_t len;
  size_t prefix_len = FILE_SYSTEM_PREFIX_LEN (name);

  for (len = strlen (name);  1 < len && ISSLASH (name[len - 1]);  len--)
    continue;

  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && len == 1
      && ISSLASH (name[0]) && ISSLASH (name[1]) && ! name[2])
    return 2;

  if (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE && prefix_len
      && len == prefix_len && ISSLASH (name[prefix_len]))
    return prefix_len + 1;

  return len;
}