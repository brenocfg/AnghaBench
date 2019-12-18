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
typedef  int u16 ;

/* Variables and functions */
 size_t ATA_ID_BUF_SIZE ; 
 size_t ATA_ID_CAPABILITY ; 
 size_t ATA_ID_COMMAND_SET_1 ; 
 size_t ATA_ID_COMMAND_SET_2 ; 
 size_t ATA_ID_CONFIG ; 
 size_t ATA_ID_CUR_CYLS ; 
 size_t ATA_ID_CUR_HEADS ; 
 size_t ATA_ID_CUR_SECTORS ; 
 size_t ATA_ID_CYLS ; 
 size_t ATA_ID_DWORD_IO ; 
 size_t ATA_ID_FIELD_VALID ; 
 size_t ATA_ID_FW_REV ; 
 size_t ATA_ID_HEADS ; 
 int ATA_ID_LBA_CAPACITY ; 
 size_t ATA_ID_MAX_MULTSECT ; 
 size_t ATA_ID_MULTSECT ; 
 size_t ATA_ID_OLD_DMA_MODES ; 
 size_t ATA_ID_OLD_PIO_MODES ; 
 size_t ATA_ID_PROD ; 
 size_t ATA_ID_SECTORS ; 
 size_t ATA_ID_SERNO ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int ata_id_u32 (int*,int) ; 

__attribute__((used)) static void isd200_dump_driveid(u16 *id)
{
	US_DEBUGP("   Identify Data Structure:\n");
	US_DEBUGP("      config = 0x%x\n",	  id[ATA_ID_CONFIG]);
	US_DEBUGP("      cyls = 0x%x\n",	  id[ATA_ID_CYLS]);
	US_DEBUGP("      heads = 0x%x\n",	  id[ATA_ID_HEADS]);
	US_DEBUGP("      track_bytes = 0x%x\n",	  id[4]);
	US_DEBUGP("      sector_bytes = 0x%x\n",  id[5]);
	US_DEBUGP("      sectors = 0x%x\n",	  id[ATA_ID_SECTORS]);
	US_DEBUGP("      serial_no[0] = 0x%x\n",  *(char *)&id[ATA_ID_SERNO]);
	US_DEBUGP("      buf_type = 0x%x\n",	  id[20]);
	US_DEBUGP("      buf_size = 0x%x\n",	  id[ATA_ID_BUF_SIZE]);
	US_DEBUGP("      ecc_bytes = 0x%x\n",	  id[22]);
	US_DEBUGP("      fw_rev[0] = 0x%x\n",	  *(char *)&id[ATA_ID_FW_REV]);
	US_DEBUGP("      model[0] = 0x%x\n",	  *(char *)&id[ATA_ID_PROD]);
	US_DEBUGP("      max_multsect = 0x%x\n",  id[ATA_ID_MAX_MULTSECT] & 0xff);
	US_DEBUGP("      dword_io = 0x%x\n",	  id[ATA_ID_DWORD_IO]);
	US_DEBUGP("      capability = 0x%x\n",	  id[ATA_ID_CAPABILITY] >> 8);
	US_DEBUGP("      tPIO = 0x%x\n",	  id[ATA_ID_OLD_PIO_MODES] >> 8);
	US_DEBUGP("      tDMA = 0x%x\n",	  id[ATA_ID_OLD_DMA_MODES] >> 8);
	US_DEBUGP("      field_valid = 0x%x\n",	  id[ATA_ID_FIELD_VALID]);
	US_DEBUGP("      cur_cyls = 0x%x\n",	  id[ATA_ID_CUR_CYLS]);
	US_DEBUGP("      cur_heads = 0x%x\n",	  id[ATA_ID_CUR_HEADS]);
	US_DEBUGP("      cur_sectors = 0x%x\n",	  id[ATA_ID_CUR_SECTORS]);
	US_DEBUGP("      cur_capacity = 0x%x\n",  ata_id_u32(id, 57));
	US_DEBUGP("      multsect = 0x%x\n",	  id[ATA_ID_MULTSECT] & 0xff);
	US_DEBUGP("      lba_capacity = 0x%x\n",  ata_id_u32(id, ATA_ID_LBA_CAPACITY));
	US_DEBUGP("      command_set_1 = 0x%x\n", id[ATA_ID_COMMAND_SET_1]);
	US_DEBUGP("      command_set_2 = 0x%x\n", id[ATA_ID_COMMAND_SET_2]);
}