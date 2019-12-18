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
struct console {int dummy; } ;
struct TYPE_2__ {unsigned char rhrb_thrb; int srb_csrb; } ;

/* Variables and functions */
 TYPE_1__ sio01 ; 

void dn_serial_console_write (struct console *co, const char *str,unsigned int count)
{
   while(count--) {
	if (*str == '\n') {
	sio01.rhrb_thrb = (unsigned char)'\r';
	while (!(sio01.srb_csrb & 0x4))
                ;
	}
    sio01.rhrb_thrb = (unsigned char)*str++;
    while (!(sio01.srb_csrb & 0x4))
            ;
  }
}