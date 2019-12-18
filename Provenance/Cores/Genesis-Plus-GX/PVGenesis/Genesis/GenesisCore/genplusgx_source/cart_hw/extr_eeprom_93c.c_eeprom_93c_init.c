#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  T_EEPROM_93C ;
struct TYPE_5__ {int data; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int custom; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_START ; 
 TYPE_2__ eeprom_93c ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sram ; 

void eeprom_93c_init()
{
  /* default eeprom state */
  memset(&eeprom_93c, 0, sizeof(T_EEPROM_93C));
  eeprom_93c.data = 1;
  eeprom_93c.state = WAIT_START;
  sram.custom = 3;
}