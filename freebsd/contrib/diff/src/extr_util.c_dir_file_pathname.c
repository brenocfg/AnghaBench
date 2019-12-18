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
 char* base_name (char const*) ; 
 char* concat (char const*,char*,char const*) ; 
 int strlen (char const*) ; 

char *
dir_file_pathname (char const *dir, char const *file)
{
  char const *base = base_name (dir);
  bool omit_slash = !*base || base[strlen (base) - 1] == '/';
  return concat (dir, "/" + omit_slash, file);
}