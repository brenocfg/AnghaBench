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
 int PIA_PACTL ; 
 int PIA_PBCTL ; 
 int PIA_PORTA ; 
 int PIA_PORTB ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static void show_PIA(void)
{
	printf("PACTL= %02X    PBCTL= %02X    PORTA= %02X    "
		   "PORTB= %02X\n", PIA_PACTL, PIA_PBCTL, PIA_PORTA, PIA_PORTB);
}