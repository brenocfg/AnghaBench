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
typedef  int /*<<< orphan*/  u16 ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM93C56A_READ ; 
 int /*<<< orphan*/  fm93c56a_cmd (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm93c56a_datain (struct scsi_qla_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm93c56a_deselect (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  fm93c56a_select (struct scsi_qla_host*) ; 

__attribute__((used)) static int eeprom_readword(int eepromAddr, u16 * value,
			   struct scsi_qla_host * ha)
{
	fm93c56a_select(ha);
	fm93c56a_cmd(ha, FM93C56A_READ, eepromAddr);
	fm93c56a_datain(ha, value);
	fm93c56a_deselect(ha);
	return 1;
}