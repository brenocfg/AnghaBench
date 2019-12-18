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
struct default_include {scalar_t__ fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char const*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 struct default_include* cpp_include_defaults ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,size_t) ; 

__attribute__((used)) static int
in_system_include_dir (const char *path)
{
  const struct default_include *p;

  gcc_assert (IS_ABSOLUTE_PATH (path));

  for (p = cpp_include_defaults; p->fname; p++)
    if (!strncmp (path, p->fname, strlen (p->fname))
	&& IS_DIR_SEPARATOR (path[strlen (p->fname)]))
      return 1;
  return 0;
}