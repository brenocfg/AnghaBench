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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct hw_data {scalar_t__ PermanentMacAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_ReadSync (struct hw_data*,int,scalar_t__*) ; 
 int /*<<< orphan*/  Wb35Reg_WriteSync (struct hw_data*,int,int) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 int cpu_to_le32 (scalar_t__) ; 

void
Uxx_ReadEthernetAddress(  struct hw_data * pHwData )
{
	u32	ltmp;

	// Reading Ethernet address from EEPROM and set into hardware due to MAC address maybe change.
	// Only unplug and plug again can make hardware read EEPROM again. 20060727
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08000000 ); // Start EEPROM access + Read + address(0x0d)
	Wb35Reg_ReadSync( pHwData, 0x03b4, &ltmp );
	*(u16 *)pHwData->PermanentMacAddress = cpu_to_le16((u16)ltmp); //20060926 anson's endian
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08010000 ); // Start EEPROM access + Read + address(0x0d)
	Wb35Reg_ReadSync( pHwData, 0x03b4, &ltmp );
	*(u16 *)(pHwData->PermanentMacAddress + 2) = cpu_to_le16((u16)ltmp); //20060926 anson's endian
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08020000 ); // Start EEPROM access + Read + address(0x0d)
	Wb35Reg_ReadSync( pHwData, 0x03b4, &ltmp );
	*(u16 *)(pHwData->PermanentMacAddress + 4) = cpu_to_le16((u16)ltmp); //20060926 anson's endian
	*(u16 *)(pHwData->PermanentMacAddress + 6) = 0;
	Wb35Reg_WriteSync( pHwData, 0x03e8, cpu_to_le32(*(u32 *)pHwData->PermanentMacAddress) ); //20060926 anson's endian
	Wb35Reg_WriteSync( pHwData, 0x03ec, cpu_to_le32(*(u32 *)(pHwData->PermanentMacAddress+4)) ); //20060926 anson's endian
}