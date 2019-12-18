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
struct re_pattern_buffer {char* fastmap; } ;

/* Variables and functions */
 int RE_SYNTAX_EMACS ; 
 int /*<<< orphan*/  error (char*,char*,char const*) ; 
 int /*<<< orphan*/  re_compile_fastmap (struct re_pattern_buffer*) ; 
 char* re_compile_pattern (char*,int /*<<< orphan*/ ,struct re_pattern_buffer*) ; 
 int re_set_syntax (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
compile_pattern (char *pattern, struct re_pattern_buffer *compiled_pattern,
		 char *fastmap)
{
  int tmp;
  const char *val;

  compiled_pattern->fastmap = fastmap;

  tmp = re_set_syntax (RE_SYNTAX_EMACS);
  val = re_compile_pattern (pattern,
			    strlen (pattern),
			    compiled_pattern);
  re_set_syntax (tmp);

  if (val)
    error ("compile_pattern: Can't compile pattern string `%s': %s!", pattern, val);

  if (fastmap)
    re_compile_fastmap (compiled_pattern);
}