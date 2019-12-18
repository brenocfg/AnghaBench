#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int offset; scalar_t__ word_en; scalar_t__* data; } ;
typedef  TYPE_1__ PGPKT_STRUCT ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 scalar_t__ EFUSE_MAX_SIZE ; 
 scalar_t__ EFUSE_REPEAT_THRESHOLD_ ; 
 scalar_t__ FALSE ; 
 scalar_t__ PG_STATE_DATA ; 
 scalar_t__ PG_STATE_HEADER ; 
 scalar_t__ TRUE ; 
 scalar_t__ efuse_CalculateWordCnts (scalar_t__) ; 
 scalar_t__ efuse_GetCurrentSize (struct net_device*) ; 
 scalar_t__ efuse_OneByteRead (struct net_device*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  efuse_OneByteWrite (struct net_device*,scalar_t__,scalar_t__) ; 
 scalar_t__ efuse_PgPacketRead (struct net_device*,int,scalar_t__*) ; 
 int /*<<< orphan*/  efuse_WordEnableDataRead (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ efuse_WordEnableDataWrite (struct net_device*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static u8 efuse_PgPacketWrite(struct net_device* dev, u8 offset, u8 word_en,u8 *data)
{
	u8 WriteState = PG_STATE_HEADER;

	bool bContinual = TRUE,bDataEmpty=TRUE, bResult = TRUE;
	u16 efuse_addr = 0;
	u8 efuse_data;

	u8 pg_header = 0;

	//u16 tmp_addr=0;
	u8 tmp_word_cnts=0,target_word_cnts=0;
	u8 tmp_header,match_word_en,tmp_word_en;

	//u8	efuse_clk_ori,efuse_clk_new;

	PGPKT_STRUCT target_pkt;
	PGPKT_STRUCT tmp_pkt;

	u8 originaldata[sizeof(u8)*8];
	u8 tmpindex = 0,badworden = 0x0F;

	static u32 repeat_times = 0;

	if( efuse_GetCurrentSize(dev) >= EFUSE_MAX_SIZE)
	{
		printk("efuse_PgPacketWrite error \n");
		return FALSE;
	}

	// Init the 8 bytes content as 0xff
	target_pkt.offset = offset;
	target_pkt.word_en= word_en;

	//PlatformFillMemory((PVOID)target_pkt.data, sizeof(u8)*8, 0xFF);
	memset(target_pkt.data,0xFF,sizeof(u8)*8);

	efuse_WordEnableDataRead(word_en,data,target_pkt.data);
	target_word_cnts = efuse_CalculateWordCnts(target_pkt.word_en);

	//efuse_reg_ctrl(pAdapter,TRUE);//power on
	printk("EFUSE Power ON\n");

	while( bContinual && (efuse_addr  < EFUSE_MAX_SIZE) )
	{

		if(WriteState==PG_STATE_HEADER)
		{
			bDataEmpty=TRUE;
			badworden = 0x0F;
			//************  so *******************
			printk("EFUSE PG_STATE_HEADER\n");
			if (	efuse_OneByteRead(dev, efuse_addr ,&efuse_data) &&
				(efuse_data!=0xFF))
			{
				tmp_header  =  efuse_data;

				tmp_pkt.offset 	= (tmp_header>>4) & 0x0F;
				tmp_pkt.word_en 	= tmp_header & 0x0F;
				tmp_word_cnts =  efuse_CalculateWordCnts(tmp_pkt.word_en);

				//************  so-1 *******************
				if(tmp_pkt.offset  != target_pkt.offset)
				{
					efuse_addr = efuse_addr + (tmp_word_cnts*2) +1; //Next pg_packet
					#if (EFUSE_ERROE_HANDLE == 1)
					WriteState = PG_STATE_HEADER;
					#endif
				}
				else
				{
					//************  so-2 *******************
					for(tmpindex=0 ; tmpindex<(tmp_word_cnts*2) ; tmpindex++)
					{
						if(efuse_OneByteRead(dev, (efuse_addr+1+tmpindex) ,&efuse_data)&&(efuse_data != 0xFF)){
							bDataEmpty = FALSE;
						}
					}
					//************  so-2-1 *******************
					if(bDataEmpty == FALSE)
					{
						efuse_addr = efuse_addr + (tmp_word_cnts*2) +1; //Next pg_packet
						#if (EFUSE_ERROE_HANDLE == 1)
						WriteState=PG_STATE_HEADER;
						#endif
					}
					else
					{//************  so-2-2 *******************
						match_word_en = 0x0F;
						if(   !( (target_pkt.word_en&BIT0)|(tmp_pkt.word_en&BIT0)  ))
						{
							 match_word_en &= (~BIT0);
						}
						if(   !( (target_pkt.word_en&BIT1)|(tmp_pkt.word_en&BIT1)  ))
						{
							 match_word_en &= (~BIT1);
						}
						if(   !( (target_pkt.word_en&BIT2)|(tmp_pkt.word_en&BIT2)  ))
						{
							 match_word_en &= (~BIT2);
						}
						if(   !( (target_pkt.word_en&BIT3)|(tmp_pkt.word_en&BIT3)  ))
						{
							 match_word_en &= (~BIT3);
						}

						//************  so-2-2-A *******************
						if((match_word_en&0x0F)!=0x0F)
						{
							badworden = efuse_WordEnableDataWrite(dev,efuse_addr+1, tmp_pkt.word_en ,target_pkt.data);

							//************  so-2-2-A-1 *******************
							//############################
							if(0x0F != (badworden&0x0F))
							{
								u8 reorg_offset = offset;
								u8 reorg_worden=badworden;
								efuse_PgPacketWrite(dev,reorg_offset,reorg_worden,originaldata);
							}
							//############################

							tmp_word_en = 0x0F;
							if(  (target_pkt.word_en&BIT0)^(match_word_en&BIT0)  )
							{
								tmp_word_en &= (~BIT0);
							}
							if(   (target_pkt.word_en&BIT1)^(match_word_en&BIT1) )
							{
								tmp_word_en &=  (~BIT1);
							}
							if(   (target_pkt.word_en&BIT2)^(match_word_en&BIT2) )
							{
								tmp_word_en &= (~BIT2);
							}
							if(   (target_pkt.word_en&BIT3)^(match_word_en&BIT3) )
							{
								tmp_word_en &=(~BIT3);
							}

							//************  so-2-2-A-2 *******************
							if((tmp_word_en&0x0F)!=0x0F){
								//reorganize other pg packet
								//efuse_addr = efuse_addr + (2*tmp_word_cnts) +1;//next pg packet addr
								efuse_addr = efuse_GetCurrentSize(dev);
								//===========================
								target_pkt.offset = offset;
								target_pkt.word_en= tmp_word_en;
								//===========================
							}else{
								bContinual = FALSE;
							}
							#if (EFUSE_ERROE_HANDLE == 1)
							WriteState=PG_STATE_HEADER;
							repeat_times++;
							if(repeat_times>EFUSE_REPEAT_THRESHOLD_){
								bContinual = FALSE;
								bResult = FALSE;
							}
							#endif
						}
						else{//************  so-2-2-B *******************
							//reorganize other pg packet
							efuse_addr = efuse_addr + (2*tmp_word_cnts) +1;//next pg packet addr
							//===========================
							target_pkt.offset = offset;
							target_pkt.word_en= target_pkt.word_en;
							//===========================
							#if (EFUSE_ERROE_HANDLE == 1)
							WriteState=PG_STATE_HEADER;
							#endif
						}
					}
				}
				printk("EFUSE PG_STATE_HEADER-1\n");
			}
			else		//************  s1: header == oxff  *******************
			{
				pg_header = ((target_pkt.offset << 4)&0xf0) |target_pkt.word_en;

				efuse_OneByteWrite(dev,efuse_addr, pg_header);
				efuse_OneByteRead(dev,efuse_addr, &tmp_header);

				if(tmp_header == pg_header)
				{ //************  s1-1*******************
					WriteState = PG_STATE_DATA;
				}
				#if (EFUSE_ERROE_HANDLE == 1)
				else if(tmp_header == 0xFF){//************  s1-3: if Write or read func doesn't work *******************
					//efuse_addr doesn't change
					WriteState = PG_STATE_HEADER;
					repeat_times++;
					if(repeat_times>EFUSE_REPEAT_THRESHOLD_){
						bContinual = FALSE;
						bResult = FALSE;
					}
				}
				#endif
				else
				{//************  s1-2 : fixed the header procedure *******************
					tmp_pkt.offset = (tmp_header>>4) & 0x0F;
					tmp_pkt.word_en=  tmp_header & 0x0F;
					tmp_word_cnts =  efuse_CalculateWordCnts(tmp_pkt.word_en);

					//************  s1-2-A :cover the exist data *******************
					memset(originaldata,0xff,sizeof(u8)*8);
					//PlatformFillMemory((PVOID)originaldata, sizeof(u8)*8, 0xff);

					if(efuse_PgPacketRead( dev, tmp_pkt.offset,originaldata))
					{	//check if data exist
						//efuse_reg_ctrl(pAdapter,TRUE);//power on
						badworden = efuse_WordEnableDataWrite(dev,efuse_addr+1,tmp_pkt.word_en,originaldata);
						//############################
						if(0x0F != (badworden&0x0F))
						{
							u8 reorg_offset = tmp_pkt.offset;
							u8 reorg_worden=badworden;
							efuse_PgPacketWrite(dev,reorg_offset,reorg_worden,originaldata);
							efuse_addr = efuse_GetCurrentSize(dev);
						}
						//############################
						else{
							efuse_addr = efuse_addr + (tmp_word_cnts*2) +1; //Next pg_packet
						}
					}
					 //************  s1-2-B: wrong address*******************
					else
					{
						efuse_addr = efuse_addr + (tmp_word_cnts*2) +1; //Next pg_packet
					}

					#if (EFUSE_ERROE_HANDLE == 1)
					WriteState=PG_STATE_HEADER;
					repeat_times++;
					if(repeat_times>EFUSE_REPEAT_THRESHOLD_){
						bContinual = FALSE;
						bResult = FALSE;
					}
					#endif

					printk("EFUSE PG_STATE_HEADER-2\n");
				}

			}

		}
		//write data state
		else if(WriteState==PG_STATE_DATA)
		{	//************  s1-1  *******************
			printk("EFUSE PG_STATE_DATA\n");
			badworden = 0x0f;
			badworden = efuse_WordEnableDataWrite(dev,efuse_addr+1,target_pkt.word_en,target_pkt.data);
			if((badworden&0x0F)==0x0F)
			{ //************  s1-1-A *******************
				bContinual = FALSE;
			}
			else
			{//reorganize other pg packet //************  s1-1-B *******************
				efuse_addr = efuse_addr + (2*target_word_cnts) +1;//next pg packet addr

				//===========================
				target_pkt.offset = offset;
				target_pkt.word_en= badworden;
				target_word_cnts =  efuse_CalculateWordCnts(target_pkt.word_en);
				//===========================
				#if (EFUSE_ERROE_HANDLE == 1)
				WriteState=PG_STATE_HEADER;
				repeat_times++;
				if(repeat_times>EFUSE_REPEAT_THRESHOLD_){
					bContinual = FALSE;
					bResult = FALSE;
				}
				#endif
				printk("EFUSE PG_STATE_HEADER-3\n");
			}
		}
	}

	//efuse_reg_ctrl(pAdapter,FALSE);//power off

	return TRUE;
}