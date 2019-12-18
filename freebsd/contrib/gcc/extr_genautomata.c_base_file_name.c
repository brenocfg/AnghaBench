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
 int strlen (char const*) ; 

__attribute__((used)) static const char *
base_file_name (const char *file_name)
{
  int directory_name_length;

  directory_name_length = strlen (file_name);
#ifdef WIN32
  while (directory_name_length >= 0 && file_name[directory_name_length] != '/'
         && file_name[directory_name_length] != '\\')
#else
  while (directory_name_length >= 0 && file_name[directory_name_length] != '/')
#endif
    directory_name_length--;
  return file_name + directory_name_length + 1;
}