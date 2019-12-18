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
 scalar_t__ type ; 
 int type_check ; 
#define  type_check_off 130 
#define  type_check_on 129 
#define  type_check_warn 128 
 scalar_t__ type_mode ; 
 scalar_t__ type_mode_auto ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
set_type_str (void)
{
  char *tmp = NULL, *prefix = "";

  if (type)
    xfree (type);
  if (type_mode == type_mode_auto)
    prefix = "auto; currently ";

  switch (type_check)
    {
    case type_check_on:
      tmp = "on";
      break;
    case type_check_off:
      tmp = "off";
      break;
    case type_check_warn:
      tmp = "warn";
      break;
    default:
      error ("Unrecognized type check setting.");
    }

  type = concat (prefix, tmp, NULL);
}