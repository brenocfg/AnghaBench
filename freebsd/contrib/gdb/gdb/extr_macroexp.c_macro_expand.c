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
struct macro_buffer {char* text; scalar_t__ last_token; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  macro_lookup_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  appendc (struct macro_buffer*,char) ; 
 int /*<<< orphan*/  cleanup_macro_buffer ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  init_buffer (struct macro_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_shared_buffer (struct macro_buffer*,char*,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct macro_buffer*) ; 
 int /*<<< orphan*/  scan (struct macro_buffer*,struct macro_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
macro_expand (const char *source,
              macro_lookup_ftype *lookup_func,
              void *lookup_func_baton)
{
  struct macro_buffer src, dest;
  struct cleanup *back_to;

  init_shared_buffer (&src, (char *) source, strlen (source));

  init_buffer (&dest, 0);
  dest.last_token = 0;
  back_to = make_cleanup (cleanup_macro_buffer, &dest);

  scan (&dest, &src, 0, lookup_func, lookup_func_baton);

  appendc (&dest, '\0');

  discard_cleanups (back_to);
  return dest.text;
}