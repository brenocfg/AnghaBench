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
 int /*<<< orphan*/  CHECKDONE (char*,char*) ; 
 int baud_rate ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  savestring (char*,int) ; 
 int /*<<< orphan*/  sr_set_debug (int) ; 
 int /*<<< orphan*/  sr_set_device (int /*<<< orphan*/ ) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

void
sr_scan_args (char *proto, char *args)
{
  int n;
  char *p, *q;

  /* if no args, then nothing to do. */
  if (args == NULL || *args == '\0')
    return;

  /* scan off white space.  */
  for (p = args; isspace (*p); ++p);;

  /* find end of device name.  */
  for (q = p; *q != '\0' && !isspace (*q); ++q);;

  /* check for missing or empty device name.  */
  CHECKDONE (p, q);
  sr_set_device (savestring (p, q - p));

  /* look for baud rate.  */
  n = strtol (q, &p, 10);

  /* check for missing or empty baud rate.  */
  CHECKDONE (p, q);
  baud_rate = n;

  /* look for debug value.  */
  n = strtol (p, &q, 10);

  /* check for missing or empty debug value.  */
  CHECKDONE (p, q);
  sr_set_debug (n);

  /* scan off remaining white space.  */
  for (p = q; isspace (*p); ++p);;

  /* if not end of string, then there's unrecognized junk. */
  if (*p != '\0')
    usage (proto, p);

  return;
}