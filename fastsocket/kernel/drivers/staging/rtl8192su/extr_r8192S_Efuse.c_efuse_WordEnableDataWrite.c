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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 int /*<<< orphan*/  PGPKT_DATA_SIZE ; 
 int /*<<< orphan*/  efuse_OneByteRead (struct net_device*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  efuse_OneByteWrite (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	u8
efuse_WordEnableDataWrite(	struct net_device*	dev,	u16 efuse_addr, u8 word_en, u8 *data)
{
	u16 tmpaddr = 0;
	u16 start_addr = efuse_addr;
	u8 badworden = 0x0F;
	//u8 NextState;
	u8 tmpdata[8];

	memset(tmpdata,0xff,PGPKT_DATA_SIZE);
	//PlatformFillMemory((PVOID)tmpdata, PGPKT_DATA_SIZE, 0xff);

	//RT_TRACE(COMP_EFUSE, "word_en = %x efuse_addr=%x\n", word_en, efuse_addr);

	//RT_PRINT_DATA(COMP_EFUSE, DBG_LOUD, ("U-EFUSE\n"), data, 8);

	if(!(word_en&BIT0))
	{
		tmpaddr = start_addr;
		efuse_OneByteWrite(dev,start_addr++, data[0]);
		efuse_OneByteWrite(dev,start_addr++, data[1]);

		efuse_OneByteRead(dev,tmpaddr, &tmpdata[0]);
		efuse_OneByteRead(dev,tmpaddr+1, &tmpdata[1]);
		if((data[0]!=tmpdata[0])||(data[1]!=tmpdata[1])){
			badworden &= (~BIT0);
		}
	}
	if(!(word_en&BIT1))
	{
		tmpaddr = start_addr;
		efuse_OneByteWrite(dev,start_addr++, data[2]);
		efuse_OneByteWrite(dev,start_addr++, data[3]);

		efuse_OneByteRead(dev,tmpaddr    , &tmpdata[2]);
		efuse_OneByteRead(dev,tmpaddr+1, &tmpdata[3]);
		if((data[2]!=tmpdata[2])||(data[3]!=tmpdata[3])){
			badworden &=( ~BIT1);
		}
	}
	if(!(word_en&BIT2))
	{
		tmpaddr = start_addr;
		efuse_OneByteWrite(dev,start_addr++, data[4]);
		efuse_OneByteWrite(dev,start_addr++, data[5]);

		efuse_OneByteRead(dev,tmpaddr, &tmpdata[4]);
		efuse_OneByteRead(dev,tmpaddr+1, &tmpdata[5]);
		if((data[4]!=tmpdata[4])||(data[5]!=tmpdata[5])){
			badworden &=( ~BIT2);
		}
	}
	if(!(word_en&BIT3))
	{
		tmpaddr = start_addr;
		efuse_OneByteWrite(dev,start_addr++, data[6]);
		efuse_OneByteWrite(dev,start_addr++, data[7]);

		efuse_OneByteRead(dev,tmpaddr, &tmpdata[6]);
		efuse_OneByteRead(dev,tmpaddr+1, &tmpdata[7]);
		if((data[6]!=tmpdata[6])||(data[7]!=tmpdata[7])){
			badworden &=( ~BIT3);
		}
	}
	return badworden;
}