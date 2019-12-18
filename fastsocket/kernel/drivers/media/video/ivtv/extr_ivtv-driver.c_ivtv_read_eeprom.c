#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tveeprom {int dummy; } ;
struct TYPE_3__ {int addr; } ;
struct ivtv {TYPE_1__ i2c_client; } ;
typedef  int /*<<< orphan*/  eedata ;

/* Variables and functions */
 int /*<<< orphan*/  tveeprom_hauppauge_analog (TYPE_1__*,struct tveeprom*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tveeprom_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void ivtv_read_eeprom(struct ivtv *itv, struct tveeprom *tv)
{
	u8 eedata[256];

	itv->i2c_client.addr = 0xA0 >> 1;
	tveeprom_read(&itv->i2c_client, eedata, sizeof(eedata));
	tveeprom_hauppauge_analog(&itv->i2c_client, tv, eedata);
}