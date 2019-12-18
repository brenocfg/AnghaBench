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
struct TYPE_2__ {int value; char* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/ * error_names ; 
 TYPE_1__ evmserr ; 
 int /*<<< orphan*/  init_error_tables () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ ** sys_errlist ; 
 int sys_nerr ; 

char *
strerror (int errnoval)
{
  const char *msg;
  static char buf[32];

#ifndef HAVE_SYS_ERRLIST

  if (error_names == NULL)
    {
      init_error_tables ();
    }

#endif

  if ((errnoval < 0) || (errnoval >= sys_nerr))
    {
#ifdef EVMSERR
      if (errnoval == evmserr.value)
	msg = evmserr.msg;
      else
#endif
      /* Out of range, just return NULL */
      msg = NULL;
    }
  else if ((sys_errlist == NULL) || (sys_errlist[errnoval] == NULL))
    {
      /* In range, but no sys_errlist or no entry at this index. */
      sprintf (buf, "Error %d", errnoval);
      msg = buf;
    }
  else
    {
      /* In range, and a valid message.  Just return the message. */
      msg = (char *) sys_errlist[errnoval];
    }
  
  return (msg);
}