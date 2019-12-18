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
typedef  int /*<<< orphan*/  state_t ;

/* Variables and functions */
 int /*<<< orphan*/  _0bbb_ ; 
 int /*<<< orphan*/  _0mbb_ ; 
 int /*<<< orphan*/  _0mfb_ ; 
 int /*<<< orphan*/  _0mfi_ ; 
 int /*<<< orphan*/  _0mib_ ; 
 int /*<<< orphan*/  _0mii_ ; 
 int /*<<< orphan*/  _0mlx_ ; 
 int /*<<< orphan*/  _0mmb_ ; 
 int /*<<< orphan*/  _0mmf_ ; 
 int /*<<< orphan*/  _0mmi_ ; 
 int /*<<< orphan*/  _1bbb_ ; 
 int /*<<< orphan*/  _1mbb_ ; 
 int /*<<< orphan*/  _1mfb_ ; 
 int /*<<< orphan*/  _1mfi_ ; 
 int /*<<< orphan*/  _1mib_ ; 
 int /*<<< orphan*/  _1mii_ ; 
 int /*<<< orphan*/  _1mlx_ ; 
 int /*<<< orphan*/  _1mmb_ ; 
 int /*<<< orphan*/  _1mmf_ ; 
 int /*<<< orphan*/  _1mmi_ ; 
 int /*<<< orphan*/  cpu_unit_reservation_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
get_template (state_t state, int pos)
{
  switch (pos)
    {
    case 3:
      if (cpu_unit_reservation_p (state, _0mmi_))
	return 1;
      else if (cpu_unit_reservation_p (state, _0mii_))
	return 0;
      else if (cpu_unit_reservation_p (state, _0mmb_))
	return 7;
      else if (cpu_unit_reservation_p (state, _0mib_))
	return 6;
      else if (cpu_unit_reservation_p (state, _0mbb_))
	return 5;
      else if (cpu_unit_reservation_p (state, _0bbb_))
	return 4;
      else if (cpu_unit_reservation_p (state, _0mmf_))
	return 3;
      else if (cpu_unit_reservation_p (state, _0mfi_))
	return 2;
      else if (cpu_unit_reservation_p (state, _0mfb_))
	return 8;
      else if (cpu_unit_reservation_p (state, _0mlx_))
	return 9;
      else
	gcc_unreachable ();
    case 6:
      if (cpu_unit_reservation_p (state, _1mmi_))
	return 1;
      else if (cpu_unit_reservation_p (state, _1mii_))
	return 0;
      else if (cpu_unit_reservation_p (state, _1mmb_))
	return 7;
      else if (cpu_unit_reservation_p (state, _1mib_))
	return 6;
      else if (cpu_unit_reservation_p (state, _1mbb_))
	return 5;
      else if (cpu_unit_reservation_p (state, _1bbb_))
	return 4;
      else if (_1mmf_ >= 0 && cpu_unit_reservation_p (state, _1mmf_))
	return 3;
      else if (cpu_unit_reservation_p (state, _1mfi_))
	return 2;
      else if (cpu_unit_reservation_p (state, _1mfb_))
	return 8;
      else if (cpu_unit_reservation_p (state, _1mlx_))
	return 9;
      else
	gcc_unreachable ();
    default:
      gcc_unreachable ();
    }
}