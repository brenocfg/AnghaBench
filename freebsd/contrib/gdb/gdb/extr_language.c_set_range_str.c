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
 scalar_t__ concat (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ range ; 
 int range_check ; 
#define  range_check_off 130 
#define  range_check_on 129 
#define  range_check_warn 128 
 scalar_t__ range_mode ; 
 scalar_t__ range_mode_auto ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
set_range_str (void)
{
  char *tmp, *pref = "";

  if (range_mode == range_mode_auto)
    pref = "auto; currently ";

  switch (range_check)
    {
    case range_check_on:
      tmp = "on";
      break;
    case range_check_off:
      tmp = "off";
      break;
    case range_check_warn:
      tmp = "warn";
      break;
    default:
      error ("Unrecognized range check setting.");
    }

  if (range)
    xfree (range);
  range = concat (pref, tmp, NULL);
}