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
copy_int (void)
{
  int type = THIS ();
  int ch;
  if (type <= 0x84)
    {
      OUT (type);
      NEXT ();
      switch (type)
	{
	case 0x84:
	  ch = THIS ();
	  NEXT ();
	  OUT (ch);
	case 0x83:
	  ch = THIS ();
	  NEXT ();
	  OUT (ch);
	case 0x82:
	  ch = THIS ();
	  NEXT ();
	  OUT (ch);
	case 0x81:
	  ch = THIS ();
	  NEXT ();
	  OUT (ch);
	case 0x80:
	  break;
	}
    }
}