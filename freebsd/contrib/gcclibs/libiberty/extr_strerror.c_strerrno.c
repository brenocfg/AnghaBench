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
struct TYPE_2__ {int value; char* name; } ;

/* Variables and functions */
 char** error_names ; 
 TYPE_1__ evmserr ; 
 int /*<<< orphan*/  init_error_tables () ; 
 int num_error_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
strerrno (int errnoval)
{
  const char *name;
  static char buf[32];

  if (error_names == NULL)
    {
      init_error_tables ();
    }

  if ((errnoval < 0) || (errnoval >= num_error_names))
    {
#ifdef EVMSERR
      if (errnoval == evmserr.value)
	name = evmserr.name;
      else
#endif
      /* Out of range, just return NULL */
      name = NULL;
    }
  else if ((error_names == NULL) || (error_names[errnoval] == NULL))
    {
      /* In range, but no error_names or no entry at this index. */
      sprintf (buf, "Error %d", errnoval);
      name = (const char *) buf;
    }
  else
    {
      /* In range, and a valid name.  Just return the name. */
      name = error_names[errnoval];
    }

  return (name);
}