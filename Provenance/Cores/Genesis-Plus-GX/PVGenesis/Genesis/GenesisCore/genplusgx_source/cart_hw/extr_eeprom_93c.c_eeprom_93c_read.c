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
struct TYPE_2__ {int cs; int data; } ;

/* Variables and functions */
 int BIT_CLK ; 
 int BIT_CS ; 
 int BIT_DATA ; 
 TYPE_1__ eeprom_93c ; 

unsigned char eeprom_93c_read(void)
{
  return ((eeprom_93c.cs << BIT_CS) | (eeprom_93c.data << BIT_DATA) | (1 << BIT_CLK));
}