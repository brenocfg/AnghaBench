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
 char const** argbuf ; 
 int argbuf_index ; 
 int argbuf_length ; 
 int have_o_argbuf_index ; 
 int /*<<< orphan*/  record_temp_file (char const*,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char** xrealloc (char const**,int) ; 

__attribute__((used)) static void
store_arg (const char *arg, int delete_always, int delete_failure)
{
  if (argbuf_index + 1 == argbuf_length)
    argbuf = xrealloc (argbuf, (argbuf_length *= 2) * sizeof (const char *));

  argbuf[argbuf_index++] = arg;
  argbuf[argbuf_index] = 0;

  if (strcmp (arg, "-o") == 0)
    have_o_argbuf_index = argbuf_index;
  if (delete_always || delete_failure)
    record_temp_file (arg, delete_always, delete_failure);
}