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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SW_3W_CMD0 ; 
 scalar_t__ SW_3W_CMD0_HOLD ; 
 scalar_t__ SW_3W_CMD1 ; 
 scalar_t__ SW_3W_CMD1_DONE ; 
 scalar_t__ SW_3W_CMD1_RE ; 
 scalar_t__ SW_3W_CMD1_WE ; 
 scalar_t__ SW_3W_DB0 ; 
 scalar_t__ SW_3W_DB1 ; 
 scalar_t__ TC_3W_POLL_MAX_TRY_CNT ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 scalar_t__ read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  read_nic_word (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

int
HwThreeWire(
	struct net_device *dev,
	u8			*pDataBuf,
	u8			nDataBufBitCnt,
	int			bHold,
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

		// Fill up data buffer for write operation.
		if(nDataBufBitCnt == 16)
		{
			write_nic_word(dev, SW_3W_DB0, *((u16 *)pDataBuf));
		}
		else if(nDataBufBitCnt == 64)
		{
			write_nic_dword(dev, SW_3W_DB0, *((u32 *)pDataBuf));
			write_nic_dword(dev, SW_3W_DB1, *((u32 *)(pDataBuf + 4)));
		}
		else
		{
			int idx;
			int ByteCnt = nDataBufBitCnt / 8;

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

		// Fill up length field.
		u1bTmp = (u8)(nDataBufBitCnt - 1); // Number of bits - 1.
		if(bHold)
			u1bTmp |= SW_3W_CMD0_HOLD;
		write_nic_byte(dev, SW_3W_CMD0, u1bTmp);

		// Set up command: WE or RE.
		if(bWrite)
		{
			write_nic_byte(dev, SW_3W_CMD1, SW_3W_CMD1_WE);
		}
		else
		{
			write_nic_byte(dev, SW_3W_CMD1, SW_3W_CMD1_RE);
		}

		// Check if WE and RE are cleared and DONE is set.
		for(TryCnt = 0; TryCnt < TC_3W_POLL_MAX_TRY_CNT; TryCnt++)
		{
			u1bTmp = read_nic_byte(dev, SW_3W_CMD1);
			if( (u1bTmp & (SW_3W_CMD1_RE|SW_3W_CMD1_WE)) == 0 &&
				(u1bTmp & SW_3W_CMD1_DONE) != 0 )
			{
				break;
			}
			udelay(10);
		}
		if(TryCnt == TC_3W_POLL_MAX_TRY_CNT)
		{
			//RT_ASSERT(TryCnt != TC_3W_POLL_MAX_TRY_CNT,
			//	("HwThreeWire(): CmdReg: %#X RE|WE bits are not clear or DONE is not set!!\n", u1bTmp));
			// Workaround suggested by wcchu: clear WE here. 2006.07.07, by rcnjko.
			write_nic_byte(dev, SW_3W_CMD1, 0);
		}

		// Read back data for read operation.
		// <RJ_TODO> I am not sure if this is correct output format of a read operation.
		if(bWrite == 0)
		{
			if(nDataBufBitCnt == 16)
			{
				*((u16 *)pDataBuf) = read_nic_word(dev, SW_3W_DB0);
			}
			else if(nDataBufBitCnt == 64)
			{
				*((u32 *)pDataBuf) = read_nic_dword(dev, SW_3W_DB0);
				*((u32 *)(pDataBuf + 4)) = read_nic_dword(dev, SW_3W_DB1);
			}
			else
			{
				int idx;
				int ByteCnt = nDataBufBitCnt / 8;

				if ((nDataBufBitCnt % 8) != 0)
					panic("HwThreeWire(): nDataBufBitCnt(%d) should be multiple of 8!!!\n",
					nDataBufBitCnt);

				if (nDataBufBitCnt > 64)
					panic("HwThreeWire(): nDataBufBitCnt(%d) should <= 64!!!\n",
					nDataBufBitCnt);

				for(idx = 0; idx < ByteCnt; idx++)
				{
					*(pDataBuf+idx) = read_nic_byte(dev, (SW_3W_DB0+idx));
				}
			}
		}

	}while(0);

	return bResult;
}