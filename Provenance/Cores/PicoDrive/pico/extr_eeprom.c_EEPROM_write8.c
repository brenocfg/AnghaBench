#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* eeprom_wb; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_write16 (unsigned char) ; 
 TYPE_2__ Pico ; 

void EEPROM_write8(unsigned int a, unsigned int d)
{
  unsigned char *wb = Pico.m.eeprom_wb;
  wb[a & 1] = d;
  EEPROM_write16((wb[0] << 8) | wb[1]);
}