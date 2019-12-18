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
 int /*<<< orphan*/  ConfigJoystick () ; 
 int /*<<< orphan*/  DetectJoystick () ; 
 int /*<<< orphan*/  UpdateJoyData () ; 
 scalar_t__ joy ; 
 int* joyBMap ; 
 int /*<<< orphan*/  joyx ; 
 int /*<<< orphan*/  joyxcenter ; 
 int /*<<< orphan*/  joyy ; 
 int /*<<< orphan*/  joyycenter ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  soundjoyer ; 
 int soundjoyeron ; 
 scalar_t__ soundo ; 

int InitJoysticks(void)
{
	if(!joy) return(0);
        if(!DetectJoystick())
        {
         printf("Joystick not detected!\n");
         joy=0;
         return 0;
        }
        if(soundo)
        {
         soundjoyeron=1;
         while(!soundjoyer);
        }
        else
         UpdateJoyData();

        joyxcenter=joyx;
        joyycenter=joyy;

        if(!(joyBMap[0]|joyBMap[1]|joyBMap[2]|joyBMap[3]))
         ConfigJoystick();
        return(1);
}