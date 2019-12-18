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
typedef  int /*<<< orphan*/  sb ;
typedef  int /*<<< orphan*/  macro_entry ;

/* Variables and functions */
 char TOLOWER (char) ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_name_beginner (char const) ; 
 scalar_t__ is_name_ender (char const) ; 
 scalar_t__ is_part_of_name (char const) ; 
 char* macro_expand (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macro_hash ; 
 int /*<<< orphan*/  macro_mri ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sb_add_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_new (int /*<<< orphan*/ *) ; 

int
check_macro (const char *line, sb *expand,
	     const char **error, macro_entry **info)
{
  const char *s;
  char *copy, *cs;
  macro_entry *macro;
  sb line_sb;

  if (! is_name_beginner (*line)
      && (! macro_mri || *line != '.'))
    return 0;

  s = line + 1;
  while (is_part_of_name (*s))
    ++s;
  if (is_name_ender (*s))
    ++s;

  copy = (char *) alloca (s - line + 1);
  memcpy (copy, line, s - line);
  copy[s - line] = '\0';
  for (cs = copy; *cs != '\0'; cs++)
    *cs = TOLOWER (*cs);

  macro = (macro_entry *) hash_find (macro_hash, copy);

  if (macro == NULL)
    return 0;

  /* Wrap the line up in an sb.  */
  sb_new (&line_sb);
  while (*s != '\0' && *s != '\n' && *s != '\r')
    sb_add_char (&line_sb, *s++);

  sb_new (expand);
  *error = macro_expand (0, &line_sb, macro, expand);

  sb_kill (&line_sb);

  /* Export the macro information if requested.  */
  if (info)
    *info = macro;

  return 1;
}