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
 int /*<<< orphan*/  fill_pathname_base (char*,char const*,size_t) ; 
 int /*<<< orphan*/  path_remove_extension (char*) ; 

void fill_pathname_base_noext(char *out,
      const char *in_path, size_t size)
{
   fill_pathname_base(out, in_path, size);
   path_remove_extension(out);
}