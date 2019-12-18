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
struct target_ops {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int target_auxv_parse (struct target_ops*,char**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int target_auxv_read (struct target_ops*,char**) ; 
 int /*<<< orphan*/  xfree (char*) ; 

int
target_auxv_search (struct target_ops *ops, CORE_ADDR match, CORE_ADDR *valp)
{
  CORE_ADDR type, val;
  char *data;
  int n = target_auxv_read (ops, &data);
  char *ptr = data;
  int ents = 0;

  if (n <= 0)
    return n;

  while (1)
    switch (target_auxv_parse (ops, &ptr, data + n, &type, &val))
      {
      case 1:			/* Here's an entry, check it.  */
	if (type == match)
	  {
	    xfree (data);
	    *valp = val;
	    return 1;
	  }
	break;
      case 0:			/* End of the vector.  */
	xfree (data);
	return 0;
      default:			/* Bogosity.  */
	xfree (data);
	return -1;
      }

  /*NOTREACHED*/
}