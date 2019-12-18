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
typedef  int uint64 ;
typedef  int int64 ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int SDL_GetTicks () ; 
 int desiredfps ; 
 int tfreq ; 

void SpeedThrottle(void)
{
 static uint64 ttime,ltime=0;
  
 waiter:
 
 ttime=SDL_GetTicks();
 ttime*=10000;

 if( (ttime-ltime) < (tfreq/desiredfps) )
 {
  int64 delay;
  delay=(tfreq/desiredfps)-(ttime-ltime);
  if(delay>0) 
   SDL_Delay(delay/10000);
  //printf("%d\n",(tfreq/desiredfps)-(ttime-ltime));
  //SDL_Delay((tfreq/desiredfps)-(ttime-ltime));
  goto waiter;
 }
 if( (ttime-ltime) >= (tfreq*4/desiredfps))
  ltime=ttime;
 else
  ltime+=tfreq/desiredfps;
}