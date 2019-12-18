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
 int /*<<< orphan*/  GROW_VECT (char*,size_t,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char tolower (char const) ; 

char *
ada_fold_name (const char *name)
{
  static char *fold_buffer = NULL;
  static size_t fold_buffer_size = 0;

  int len = strlen (name);
  GROW_VECT (fold_buffer, fold_buffer_size, len + 1);

  if (name[0] == '\'')
    {
      strncpy (fold_buffer, name + 1, len - 2);
      fold_buffer[len - 2] = '\000';
    }
  else
    {
      int i;
      for (i = 0; i <= len; i += 1)
	fold_buffer[i] = tolower (name[i]);
    }

  return fold_buffer;
}