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
typedef  unsigned long uint32 ;

/* Variables and functions */
 int JOY_DOWN ; 
 int JOY_LEFT ; 
 int JOY_RIGHT ; 
 int JOY_UP ; 
 int /*<<< orphan*/  UpdateJoyData () ; 
 int joy ; 
 int* joyBMap ; 
 int joybuttons ; 
 double joyx ; 
 double joyxcenter ; 
 double joyy ; 
 double joyycenter ; 
 int /*<<< orphan*/  soundo ; 

uint32 GetJSOr(void)
{
        int y;
        unsigned long ret;
	static int rtoggle=0;
        ret=0;

	rtoggle^=1;
        if(!soundo)
         UpdateJoyData();
        for(y=0;y<6;y++)
	 if((y>=4 && rtoggle) || y<4)
          if(joybuttons&joyBMap[y]) ret|=(1<<y&3)<<((joy-1)<<3);

        if(joyx<=joyxcenter*.25) ret|=JOY_LEFT<<((joy-1)<<3);
        else if(joyx>=joyxcenter*1.75) ret|=JOY_RIGHT<<((joy-1)<<3);
        if(joyy<=joyycenter*.25) ret|=JOY_UP<<((joy-1)<<3);
        else if(joyy>=joyycenter*1.75) ret|=JOY_DOWN<<((joy-1)<<3);

        return ret;
}