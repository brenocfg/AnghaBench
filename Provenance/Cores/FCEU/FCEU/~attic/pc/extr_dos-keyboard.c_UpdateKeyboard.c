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
 size_t SCAN_C ; 
 size_t SCAN_LEFTCONTROL ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__* keybuf ; 
 int newk ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

int UpdateKeyboard(void)
{
 int t=newk;

 if(t)
 {
  asm volatile(
        "subl %%eax,_newk\n\t"
	:
	: "a" (t)
  );

  if(keybuf[SCAN_LEFTCONTROL] && keybuf[SCAN_C])
   raise(SIGINT);
  return(1);
 }
 return(0);
}