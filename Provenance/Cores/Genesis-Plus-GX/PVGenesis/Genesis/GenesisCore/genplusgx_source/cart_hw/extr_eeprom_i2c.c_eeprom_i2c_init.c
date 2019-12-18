#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  T_EEPROM_I2C ;
typedef  int /*<<< orphan*/  T_CONFIG_I2C ;
struct TYPE_19__ {int chk; int /*<<< orphan*/  config; int /*<<< orphan*/  game_id; } ;
struct TYPE_18__ {TYPE_1__* memory_map; } ;
struct TYPE_17__ {int sda_out_adr; int sda_in_adr; int scl_adr; } ;
struct TYPE_16__ {int sda; int old_sda; int scl; int old_scl; TYPE_6__ config; int /*<<< orphan*/  state; } ;
struct TYPE_15__ {int realchecksum; int /*<<< orphan*/  product; } ;
struct TYPE_14__ {int custom; int on; int end; int start; scalar_t__ detected; } ;
struct TYPE_13__ {void* write; void* read; } ;
struct TYPE_12__ {int /*<<< orphan*/  write16; void* write8; void* read16; void* read8; } ;
struct TYPE_11__ {int /*<<< orphan*/  rom; } ;

/* Variables and functions */
 int GAME_CNT ; 
 int READ_BYTE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAND_BY ; 
 TYPE_10__ cart ; 
 TYPE_9__* database ; 
 TYPE_5__ eeprom_i2c ; 
 void* eeprom_i2c_read_byte ; 
 void* eeprom_i2c_read_word ; 
 void* eeprom_i2c_write_byte ; 
 int /*<<< orphan*/  eeprom_i2c_write_word ; 
 TYPE_7__ m68k ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ rominfo ; 
 TYPE_3__ sram ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zbank_memory_map ; 

void eeprom_i2c_init()
{
  int i = 0;

  /* initialize eeprom */
  memset(&eeprom_i2c, 0, sizeof(T_EEPROM_I2C));
  eeprom_i2c.sda = eeprom_i2c.old_sda = 1;
  eeprom_i2c.scl = eeprom_i2c.old_scl = 1;
  eeprom_i2c.state = STAND_BY;

  /* no eeprom by default */
  sram.custom = 0;

  /* look into game database */
  while (i<GAME_CNT)
  {
    if (strstr(rominfo.product,database[i].game_id) != NULL)
    {
      /* additional check (Micro Machines, Rockman Mega World) */
      if ((database[i].chk == 0x0000) || (database[i].chk == rominfo.realchecksum))
      {
        sram.custom = 1;
        sram.on = 1;
        memcpy(&eeprom_i2c.config, &database[i].config, sizeof(T_CONFIG_I2C));
        i = GAME_CNT;
      }
    }
    i++;
  }

  /* Game not found in database but ROM header indicates it uses serial EEPROM */
  if (!sram.custom && sram.detected)
  {
    if ((READ_BYTE(cart.rom,0x1b2) == 0xe8) || ((sram.end - sram.start) < 2))
    {
      /* set SEGA mapper as default */
      sram.custom = 1;
      memcpy(&eeprom_i2c.config, &database[9].config, sizeof(T_CONFIG_I2C));
    }
  }

  /* initialize m68k bus handlers */
  if (sram.custom)
  {
    m68k.memory_map[eeprom_i2c.config.sda_out_adr >> 16].read8   = eeprom_i2c_read_byte;
    m68k.memory_map[eeprom_i2c.config.sda_out_adr >> 16].read16  = eeprom_i2c_read_word;
    m68k.memory_map[eeprom_i2c.config.sda_in_adr >> 16].read8    = eeprom_i2c_read_byte;
    m68k.memory_map[eeprom_i2c.config.sda_in_adr >> 16].read16   = eeprom_i2c_read_word;
    m68k.memory_map[eeprom_i2c.config.scl_adr >> 16].write8      = eeprom_i2c_write_byte;
    m68k.memory_map[eeprom_i2c.config.scl_adr >> 16].write16     = eeprom_i2c_write_word;
    zbank_memory_map[eeprom_i2c.config.sda_out_adr >> 16].read   = eeprom_i2c_read_byte;
    zbank_memory_map[eeprom_i2c.config.sda_in_adr >> 16].read    = eeprom_i2c_read_byte;
    zbank_memory_map[eeprom_i2c.config.scl_adr >> 16].write      = eeprom_i2c_write_byte;
  }
}