#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** error_names ; 
 TYPE_1__ evmserr ; 
 int /*<<< orphan*/  init_error_tables () ; 
 int num_error_names ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
strtoerrno (const char *name)
{
  int errnoval = 0;

  if (name != NULL)
    {
      if (error_names == NULL)
	{
	  init_error_tables ();
	}
      for (errnoval = 0; errnoval < num_error_names; errnoval++)
	{
	  if ((error_names[errnoval] != NULL) &&
	      (strcmp (name, error_names[errnoval]) == 0))
	    {
	      break;
	    }
	}
      if (errnoval == num_error_names)
	{
#ifdef EVMSERR
	  if (strcmp (name, evmserr.name) == 0)
	    errnoval = evmserr.value;
	  else
#endif
	  errnoval = 0;
	}
    }
  return (errnoval);
}