#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long Channels; unsigned long Targets; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 unsigned long simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static bool DAC960_ParsePhysicalDevice(DAC960_Controller_T *Controller,
					  char *UserCommandString,
					  unsigned char *Channel,
					  unsigned char *TargetID)
{
  char *NewUserCommandString = UserCommandString;
  unsigned long XChannel, XTargetID;
  while (*UserCommandString == ' ') UserCommandString++;
  if (UserCommandString == NewUserCommandString)
    return false;
  XChannel = simple_strtoul(UserCommandString, &NewUserCommandString, 10);
  if (NewUserCommandString == UserCommandString ||
      *NewUserCommandString != ':' ||
      XChannel >= Controller->Channels)
    return false;
  UserCommandString = ++NewUserCommandString;
  XTargetID = simple_strtoul(UserCommandString, &NewUserCommandString, 10);
  if (NewUserCommandString == UserCommandString ||
      *NewUserCommandString != '\0' ||
      XTargetID >= Controller->Targets)
    return false;
  *Channel = XChannel;
  *TargetID = XTargetID;
  return true;
}