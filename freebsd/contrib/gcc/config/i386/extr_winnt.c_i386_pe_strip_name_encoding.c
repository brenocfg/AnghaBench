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
 int /*<<< orphan*/  DLL_EXPORT_PREFIX ; 
 int /*<<< orphan*/  DLL_IMPORT_PREFIX ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
i386_pe_strip_name_encoding (const char *str)
{
  if (strncmp (str, DLL_IMPORT_PREFIX, strlen (DLL_IMPORT_PREFIX))
      == 0)
    str += strlen (DLL_IMPORT_PREFIX);
  else if (strncmp (str, DLL_EXPORT_PREFIX, strlen (DLL_EXPORT_PREFIX))
	   == 0)
    str += strlen (DLL_EXPORT_PREFIX);
  if (*str == '*')
    str += 1;
  return str;
}