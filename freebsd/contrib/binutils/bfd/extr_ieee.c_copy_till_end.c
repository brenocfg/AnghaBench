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
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  OUT (int) ; 
 int THIS () ; 

__attribute__((used)) static void
copy_till_end (void)
{
  int ch = THIS ();

  while (1)
    {
      while (ch <= 0x80)
	{
	  OUT (ch);
	  NEXT ();
	  ch = THIS ();
	}
      switch (ch)
	{
	case 0x84:
	  OUT (THIS ());
	  NEXT ();
	case 0x83:
	  OUT (THIS ());
	  NEXT ();
	case 0x82:
	  OUT (THIS ());
	  NEXT ();
	case 0x81:
	  OUT (THIS ());
	  NEXT ();
	  OUT (THIS ());
	  NEXT ();

	  ch = THIS ();
	  break;
	default:
	  return;
	}
    }

}