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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EFUSE_Read1Byte (struct net_device*,int) ; 
 int /*<<< orphan*/  ReadEFuseByte (struct net_device*,int,int*) ; 
 int /*<<< orphan*/  printk (char*) ; 

void
ReadEFuse(struct net_device* dev, u16	 _offset, u16 _size_byte, u8 *pbuf)
{

	u8  	efuseTbl[128];
	u8  	rtemp8[1];
	u16 	eFuse_Addr = 0;
	u8  	offset, wren;
	u16  	i, j;
	u16 	eFuseWord[16][4];// = {0xFF};//FIXLZM

	for(i=0; i<16; i++)
		for(j=0; j<4; j++)
			eFuseWord[i][j]=0xFF;

	// Do NOT excess total size of EFuse table. Added by Roger, 2008.11.10.
	if((_offset + _size_byte)>128)
	{// total E-Fuse table is 128bytes
		//RT_TRACE(COMP_EFUSE, "ReadEFuse(): Invalid offset(%#x) with read bytes(%#x)!!\n",_offset, _size_byte);
		printk("ReadEFuse(): Invalid offset with read bytes!!\n");
		return;
	}

	// Refresh efuse init map as all oxFF.
	for (i = 0; i < 128; i++)
		efuseTbl[i] = 0xFF;

#if (EFUSE_READ_SWITCH == 1)
	ReadEFuseByte(dev, eFuse_Addr, rtemp8);
#else
	rtemp8[0] = EFUSE_Read1Byte(dev, eFuse_Addr);
#endif
	if(*rtemp8 != 0xFF)		eFuse_Addr++;
	while((*rtemp8 != 0xFF) && (eFuse_Addr < 512)){
		offset = ((*rtemp8 >> 4) & 0x0f);
		if(offset <= 0x0F){
			wren = (*rtemp8 & 0x0f);
			for(i=0; i<4; i++){
				if(!(wren & 0x01)){
#if (EFUSE_READ_SWITCH == 1)
					ReadEFuseByte(dev, eFuse_Addr, rtemp8);	eFuse_Addr++;
#else
					rtemp8[0] = EFUSE_Read1Byte(dev, eFuse_Addr);	eFuse_Addr++;
#endif
					eFuseWord[offset][i] = (*rtemp8 & 0xff);
					if(eFuse_Addr >= 512) break;
#if (EFUSE_READ_SWITCH == 1)
					ReadEFuseByte(dev, eFuse_Addr, rtemp8);	eFuse_Addr++;
#else
					rtemp8[0] = EFUSE_Read1Byte(dev, eFuse_Addr);	eFuse_Addr++;
#endif
					eFuseWord[offset][i] |= (((u16)*rtemp8 << 8) & 0xff00);
					if(eFuse_Addr >= 512) break;
				}
				wren >>= 1;
			}
		}
#if (EFUSE_READ_SWITCH == 1)
		ReadEFuseByte(dev, eFuse_Addr, rtemp8);
#else
		rtemp8[0] = EFUSE_Read1Byte(dev, eFuse_Addr);	eFuse_Addr++;
#endif
		if(*rtemp8 != 0xFF && (eFuse_Addr < 512))	eFuse_Addr++;
	}

	for(i=0; i<16; i++){
		for(j=0; j<4; j++){
			efuseTbl[(i*8)+(j*2)]=(eFuseWord[i][j] & 0xff);
			efuseTbl[(i*8)+((j*2)+1)]=((eFuseWord[i][j] >> 8) & 0xff);
		}
	}
	for(i=0; i<_size_byte; i++)
		pbuf[i] = efuseTbl[_offset+i];
}