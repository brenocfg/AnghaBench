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
 int /*<<< orphan*/  apr_isdigit (char const) ; 

__attribute__((used)) static int
compare_left(char const *a, char const *b)
{
     /* Compare two left-aligned numbers: the first to have a
        different value wins. */
     for (;; a++, b++) {
	  if (!apr_isdigit(*a)  &&  !apr_isdigit(*b))
	       break;
	  else if (!apr_isdigit(*a))
	       return -1;
	  else if (!apr_isdigit(*b))
	       return +1;
	  else if (*a < *b)
	       return -1;
	  else if (*a > *b)
	       return +1;
     }
	  
     return 0;
}