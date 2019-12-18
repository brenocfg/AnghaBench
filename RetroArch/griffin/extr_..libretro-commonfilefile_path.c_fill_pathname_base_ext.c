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
 int /*<<< orphan*/  fill_pathname_base_noext (char*,char const*,size_t) ; 
 size_t strlcat (char*,char const*,size_t) ; 

size_t fill_pathname_base_ext(char *out,
      const char *in_path, const char *ext,
      size_t size)
{
   fill_pathname_base_noext(out, in_path, size);
   return strlcat(out, ext, size);
}