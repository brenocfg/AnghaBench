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
 int /*<<< orphan*/  add_path (char*,size_t,int /*<<< orphan*/ ,int) ; 
 char const* cpp_GCC_INCLUDE_DIR ; 
 size_t cpp_GCC_INCLUDE_DIR_len ; 
 char const* iprefix ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static void
add_prefixed_path (const char *suffix, size_t chain)
{
  char *path;
  const char *prefix;
  size_t prefix_len, suffix_len;

  suffix_len = strlen (suffix);
  prefix     = iprefix ? iprefix : cpp_GCC_INCLUDE_DIR;
  prefix_len = iprefix ? strlen (iprefix) : cpp_GCC_INCLUDE_DIR_len;

  path = (char *) xmalloc (prefix_len + suffix_len + 1);
  memcpy (path, prefix, prefix_len);
  memcpy (path + prefix_len, suffix, suffix_len);
  path[prefix_len + suffix_len] = '\0';

  add_path (path, chain, 0, false);
}