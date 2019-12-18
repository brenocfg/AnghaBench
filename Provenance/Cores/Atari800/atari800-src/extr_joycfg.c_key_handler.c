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
 int* buffer ; 
 int ext ; 
 int hi ; 
 int inportb (int) ; 
 int key ; 
 int left ; 
 int /*<<< orphan*/  outportb (int,int) ; 
 int raw_key ; 

void key_handler(void)
{
	asm("cli; pusha");
	raw_key = inportb(0x60);
        if (ext==2) ext=1;else /*ext 2 is used for pause*/
        if (ext==1)
        {
            left=raw_key&0x80;
            key=(raw_key&0x7f)+128;
            buffer[hi++]=key+(left<<8);
            if (hi==100) hi=0;
            ext=0;
        } else
        {
          key=raw_key&0x7f;
          left=raw_key&0x80;
          switch(raw_key)
          {
            case 0xe1:ext=2;break;
            case 0xe0:ext=1;break;
            default:
              buffer[hi++]=key+(left<<8);
              if (hi==100) hi=0;
          }
        }
	outportb(0x20, 0x20);
	asm("popa; sti");
}