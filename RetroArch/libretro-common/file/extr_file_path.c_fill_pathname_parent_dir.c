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
 int /*<<< orphan*/  path_parent_dir (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

void fill_pathname_parent_dir(char *out_dir,
      const char *in_dir, size_t size)
{
   if (out_dir != in_dir)
      strlcpy(out_dir, in_dir, size);
   path_parent_dir(out_dir);
}