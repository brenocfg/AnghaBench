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
 int THIS () ; 
 int /*<<< orphan*/  e2_record () ; 
 int /*<<< orphan*/  f0_record () ; 
 int /*<<< orphan*/  f1_record () ; 
 int /*<<< orphan*/  f2_record () ; 
 int /*<<< orphan*/  f8_record () ; 

__attribute__((used)) static void
block (void)
{
  int ch;

  while (1)
    {
      ch = THIS ();
      switch (ch)
	{
	case 0xe1:
	case 0xe5:
	  return;
	case 0xf9:
	  return;
	case 0xf0:
	  f0_record ();
	  break;
	case 0xf1:
	  f1_record ();
	  break;
	case 0xf2:
	  f2_record ();
	  break;
	case 0xf8:
	  f8_record ();
	  break;
	case 0xe2:
	  e2_record ();
	  break;

	}
    }
}