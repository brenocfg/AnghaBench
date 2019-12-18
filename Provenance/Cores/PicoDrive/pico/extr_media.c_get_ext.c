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
 int /*<<< orphan*/  strlwr_ (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void get_ext(const char *file, char *ext)
{
  const char *p;

  p = file + strlen(file) - 4;
  if (p < file) p = file;
  strncpy(ext, p, 4);
  ext[4] = 0;
  strlwr_(ext);
}