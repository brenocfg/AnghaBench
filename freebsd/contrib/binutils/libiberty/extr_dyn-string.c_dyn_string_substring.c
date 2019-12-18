#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dyn_string_t ;
struct TYPE_5__ {int length; char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * dyn_string_resize (TYPE_1__*,int) ; 

int
dyn_string_substring (dyn_string_t dest, dyn_string_t src,
                      int start, int end)
{
  int i;
  int length = end - start;

  if (start > end || start > src->length || end > src->length)
    abort ();

  /* Make room for the substring.  */
  if (dyn_string_resize (dest, length) == NULL)
    return 0;
  /* Copy the characters in the substring,  */
  for (i = length; --i >= 0; )
    dest->s[i] = src->s[start + i];
  /* NUL-terimate the result.  */
  dest->s[length] = '\0';
  /* Record the length of the substring.  */
  dest->length = length;

  return 1;
}