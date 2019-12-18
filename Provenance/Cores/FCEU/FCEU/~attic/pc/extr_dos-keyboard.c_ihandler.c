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
typedef  int /*<<< orphan*/  _go32_dpmi_registers ;

/* Variables and functions */
 unsigned char SCAN_LEFTALT ; 
 unsigned char SCAN_LEFTCONTROL ; 
 unsigned char inp (int) ; 
 unsigned char* keybuf ; 
 int lastsc ; 
 int /*<<< orphan*/  newk ; 
 int /*<<< orphan*/  outp (int,int) ; 

__attribute__((used)) static void ihandler(_go32_dpmi_registers *r)
{
 unsigned char scode=inp(0x60);	/* Get scan code. */


 if(scode!=0xE0)
 {
  int offs=0;

  /* I'm only interested in preserving the independent status of the
     right ALT and CONTROL keys.
  */
  if(lastsc==0xE0)
   if((scode&0x7F)==SCAN_LEFTALT || (scode&0x7F)==SCAN_LEFTCONTROL)
    offs=0x80;
  

  keybuf[(scode&0x7f)|offs]=((scode&0x80)^0x80);
  newk++;
 }
 lastsc=scode;

 outp(0x20,0x20);	/* Acknowledge interrupt. */
}