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
 unsigned long SG_CTS ; 
 unsigned long SG_DCD ; 
 unsigned long SG_DSR ; 
 unsigned long SG_DTR ; 
 unsigned long SG_RI ; 
 unsigned long SG_RTS ; 
 long TIOCM_CD ; 
 long TIOCM_CTS ; 
 long TIOCM_DSR ; 
 long TIOCM_DTR ; 
 long TIOCM_RI ; 
 long TIOCM_RTS ; 

__attribute__((used)) static long stli_mktiocm(unsigned long sigvalue)
{
	long	tiocm = 0;
	tiocm |= ((sigvalue & SG_DCD) ? TIOCM_CD : 0);
	tiocm |= ((sigvalue & SG_CTS) ? TIOCM_CTS : 0);
	tiocm |= ((sigvalue & SG_RI) ? TIOCM_RI : 0);
	tiocm |= ((sigvalue & SG_DSR) ? TIOCM_DSR : 0);
	tiocm |= ((sigvalue & SG_DTR) ? TIOCM_DTR : 0);
	tiocm |= ((sigvalue & SG_RTS) ? TIOCM_RTS : 0);
	return(tiocm);
}