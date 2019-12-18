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
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ DTestButton (int /*<<< orphan*/ *) ; 
 scalar_t__ FCEUI_IsMovieActive () ; 
 int /*<<< orphan*/ ** GamePadConfig ; 
 int JSreturn ; 

__attribute__((used)) static void UpdateGamepad(void)
{
 if(FCEUI_IsMovieActive()<0)
   return;

 static int rapid=0;
 uint32 JS=0;
 int x;
 int wg;

 rapid^=1;

 for(wg=0;wg<4;wg++)
 {
  for(x=0;x<8;x++)
   if(DTestButton(&GamePadConfig[wg][x]))
    JS|=(1<<x)<<(wg<<3);

  if(rapid)
   for(x=0;x<2;x++)
     if(DTestButton(&GamePadConfig[wg][8+x]))
      JS|=(1<<x)<<(wg<<3);
  }

//  for(x=0;x<32;x+=8)	/* Now, test to see if anything weird(up+down at same time)
//			   is happening, and correct */
//  {
//   if((JS & (0xC0<<x) ) == (0xC0<<x) ) JS&=~(0xC0<<x);
//   if((JS & (0x30<<x) ) == (0x30<<x) ) JS&=~(0x30<<x);
//  }

  JSreturn=JS;
}