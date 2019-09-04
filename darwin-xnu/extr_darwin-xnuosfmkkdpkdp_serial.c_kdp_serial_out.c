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
 unsigned char SKDP_END_CHAR ; 
 unsigned char SKDP_ESC_CHAR ; 
 unsigned char SKDP_START_CHAR ; 

__attribute__((used)) static void kdp_serial_out(unsigned char byte, void (*outFunc)(char))
{
	//need to escape '\n' because the kernel serial output turns it into a cr/lf
	if(byte == SKDP_START_CHAR || byte == SKDP_END_CHAR || byte == SKDP_ESC_CHAR || byte == '\n')
	{
		outFunc(SKDP_ESC_CHAR);
		byte = ~byte;
	}
	outFunc(byte);
}