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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT3 ; 
 int /*<<< orphan*/  PI_DATA_READ ; 
 scalar_t__ RFPinsSelect ; 
 scalar_t__ RF_SW_CFG_SI ; 
 scalar_t__ RF_SW_CONFIG ; 
 int /*<<< orphan*/  SI_DATA_READ ; 
 scalar_t__ SW_3W_CMD1 ; 
 scalar_t__ SW_3W_CMD1_DONE ; 
 scalar_t__ SW_3W_CMD1_RE ; 
 scalar_t__ SW_3W_CMD1_WE ; 
 scalar_t__ SW_3W_DB0 ; 
 scalar_t__ SW_3W_DB1 ; 
 scalar_t__ TC_3W_POLL_MAX_TRY_CNT ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 scalar_t__ read_nic_byte (struct net_device*,scalar_t__) ; 
 int read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int) ; 

int
HwHSSIThreeWire(
	struct net_device *dev,
	u8			*pDataBuf,
	u8			nDataBufBitCnt,
	int			bSI,
	int			bWrite
	)
{
	int	bResult = 1;
	u8	TryCnt;
	u8	u1bTmp;

	do
	{
		// Check if WE and RE are cleared.
		for(TryCnt = 0; TryCnt < TC_3W_POLL_MAX_TRY_CNT; TryCnt++)
		{
			u1bTmp = read_nic_byte(dev, SW_3W_CMD1);
			if( (u1bTmp & (SW_3W_CMD1_RE|SW_3W_CMD1_WE)) == 0 )
			{
				break;
			}
			udelay(10);
		}
		if (TryCnt == TC_3W_POLL_MAX_TRY_CNT)
			panic("HwThreeWire(): CmdReg: %#X RE|WE bits are not clear!!\n", u1bTmp);

		// RTL8187S HSSI Read/Write Function
		u1bTmp = read_nic_byte(dev, RF_SW_CONFIG);

		if(bSI)
		{
			u1bTmp |=   RF_SW_CFG_SI;   //reg08[1]=1 Serial Interface(SI)
		}else
		{
			u1bTmp &= ~RF_SW_CFG_SI;  //reg08[1]=0 Parallel Interface(PI)
		}

		write_nic_byte(dev, RF_SW_CONFIG, u1bTmp);

		if(bSI)
		{
			// jong: HW SI read must set reg84[3]=0.
			u1bTmp = read_nic_byte(dev, RFPinsSelect);
			u1bTmp &= ~BIT3;
			write_nic_byte(dev, RFPinsSelect, u1bTmp );
		}
	 	// Fill up data buffer for write operation.

		if(bWrite)
		{
			if(nDataBufBitCnt == 16)
			{
				write_nic_word(dev, SW_3W_DB0, *((u16*)pDataBuf));
			}
			else if(nDataBufBitCnt == 64)  // RTL8187S shouldn't enter this case
			{
				write_nic_dword(dev, SW_3W_DB0, *((u32*)pDataBuf));
				write_nic_dword(dev, SW_3W_DB1, *((u32*)(pDataBuf + 4)));
			}
			else
			{
				int idx;
				int ByteCnt = nDataBufBitCnt / 8;
                                //printk("%d\n",nDataBufBitCnt);
				if ((nDataBufBitCnt % 8) != 0)
				panic("HwThreeWire(): nDataBufBitCnt(%d) should be multiple of 8!!!\n",
				nDataBufBitCnt);

			       if (nDataBufBitCnt > 64)
				panic("HwThreeWire(): nDataBufBitCnt(%d) should <= 64!!!\n",
				nDataBufBitCnt);

				for(idx = 0; idx < ByteCnt; idx++)
				{
					write_nic_byte(dev, (SW_3W_DB0+idx), *(pDataBuf+idx));
				}
			}
		}
		else		//read
		{
			if(bSI)
			{
				// SI - reg274[3:0] : RF register's Address
				write_nic_word(dev, SW_3W_DB0, *((u16*)pDataBuf) );
			}
			else
			{
				// PI - reg274[15:12] : RF register's Address
				write_nic_word(dev, SW_3W_DB0, (*((u16*)pDataBuf)) << 12);
			}
		}

		// Set up command: WE or RE.
		if(bWrite)
		{
			write_nic_byte(dev, SW_3W_CMD1, SW_3W_CMD1_WE);
		}
		else
		{
			write_nic_byte(dev, SW_3W_CMD1, SW_3W_CMD1_RE);
		}

		// Check if DONE is set.
		for(TryCnt = 0; TryCnt < TC_3W_POLL_MAX_TRY_CNT; TryCnt++)
		{
			u1bTmp = read_nic_byte(dev, SW_3W_CMD1);
			if(  (u1bTmp & SW_3W_CMD1_DONE) != 0 )
			{
				break;
			}
			udelay(10);
		}

		write_nic_byte(dev, SW_3W_CMD1, 0);

		// Read back data for read operation.
		if(bWrite == 0)
		{
			if(bSI)
			{
				//Serial Interface : reg363_362[11:0]
				*((u16*)pDataBuf) = read_nic_word(dev, SI_DATA_READ) ;
			}
			else
			{
				//Parallel Interface : reg361_360[11:0]
				*((u16*)pDataBuf) = read_nic_word(dev, PI_DATA_READ);
			}

			*((u16*)pDataBuf) &= 0x0FFF;
		}

	}while(0);

	return bResult;
}