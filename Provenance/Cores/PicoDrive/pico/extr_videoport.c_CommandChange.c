#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct PicoVideo {unsigned int command; unsigned char type; unsigned short addr; } ;
struct TYPE_2__ {struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommandDma () ; 
 TYPE_1__ Pico ; 

__attribute__((used)) static void CommandChange(void)
{
  struct PicoVideo *pvid=&Pico.video;
  unsigned int cmd=0,addr=0;

  cmd=pvid->command;

  // Get type of transfer 0xc0000030 (v/c/vsram read/write)
  pvid->type=(unsigned char)(((cmd>>2)&0xc)|(cmd>>30));

  // Get address 0x3fff0003
  addr =(cmd>>16)&0x3fff;
  addr|=(cmd<<14)&0xc000;
  pvid->addr=(unsigned short)addr;

  // Check for dma:
  if (cmd&0x80) CommandDma();
}