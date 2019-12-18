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
typedef  int /*<<< orphan*/  uInt ;
typedef  int Unit ;
typedef  int Int ;

/* Variables and functions */
 int DECDPUN ; 
 int* powers ; 

__attribute__((used)) static Int
decGetDigits (const Unit * uar, Int len)
{
  const Unit *up = uar + len - 1;	/* -> msu */
  Int digits = len * DECDPUN;	/* maximum possible digits */
  uInt const *pow;		/* work */

  for (; up >= uar; up--)
    {
      digits -= DECDPUN;
      if (*up == 0)
	{			/* unit is 0 */
	  if (digits != 0)
	    continue;		/* more to check */
	  /* all units were 0 */
	  digits++;		/* .. so bump digits to 1 */
	  break;
	}
      /* found the first non-zero Unit */
      digits++;
      if (*up < 10)
	break;			/* fastpath 1-9 */
      digits++;
      for (pow = &powers[2]; *up >= *pow; pow++)
	digits++;
      break;
    }				/* up */

  return digits;
}