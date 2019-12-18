#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wbsoft_priv {int dummy; } ;
struct wb35_descriptor {int FragmentThreshold; int TxRate; int FragmentCount; } ;
struct TYPE_4__ {void* value; scalar_t__ T00_frame_length; } ;
struct TYPE_3__ {int T01_add_rts; int T01_add_cts; int T01_rts_cts_duration; void* value; scalar_t__ T01_plcp_header_length; scalar_t__ T01_modulation_type; } ;
typedef  TYPE_1__* PT01_DESCRIPTOR ;
typedef  TYPE_2__* PT00_DESCRIPTOR ;

/* Variables and functions */
 scalar_t__ CURRENT_PROTECT_MECHANISM ; 
 int CURRENT_RTS_THRESHOLD ; 
 int DEFAULT_SIFSTIME ; 
 int DOT_11_DA_OFFSET ; 
 int LONG_PREAMBLE_PLUS_PLCPHEADER_TIME ; 
 int PREAMBLE_PLUS_SIGNAL_PLUS_SIGNALEXTENSION ; 
 int SHORT_PREAMBLE_PLUS_PLCPHEADER_TIME ; 
 int Tsym ; 
 int cpu_to_le16 (int) ; 
 void* cpu_to_le32 (void*) ; 

__attribute__((used)) static void Mds_DurationSet(struct wbsoft_priv *adapter,  struct wb35_descriptor *pDes,  u8 *buffer)
{
	PT00_DESCRIPTOR	pT00;
	PT01_DESCRIPTOR	pT01;
	u16	Duration, NextBodyLen, OffsetSize;
	u8	Rate, i;
	unsigned char	CTS_on = false, RTS_on = false;
	PT00_DESCRIPTOR pNextT00;
	u16 BodyLen = 0;
	unsigned char boGroupAddr = false;

	OffsetSize = pDes->FragmentThreshold + 32 + 3;
	OffsetSize &= ~0x03;
	Rate = pDes->TxRate >> 1;
	if (!Rate)
		Rate = 1;

	pT00 = (PT00_DESCRIPTOR)buffer;
	pT01 = (PT01_DESCRIPTOR)(buffer+4);
	pNextT00 = (PT00_DESCRIPTOR)(buffer+OffsetSize);

	if( buffer[ DOT_11_DA_OFFSET+8 ] & 0x1 ) // +8 for USB hdr
		boGroupAddr = true;

	//========================================
	// Set RTS/CTS mechanism
	//========================================
	if (!boGroupAddr)
	{
		//NOTE : If the protection mode is enabled and the MSDU will be fragmented,
		//		 the tx rates of MPDUs will all be DSSS rates. So it will not use
		//		 CTS-to-self in this case. CTS-To-self will only be used when without
		//		 fragmentation. -- 20050112
		BodyLen = (u16)pT00->T00_frame_length;	//include 802.11 header
		BodyLen += 4;	//CRC

		if( BodyLen >= CURRENT_RTS_THRESHOLD )
			RTS_on = true; // Using RTS
		else
		{
			if( pT01->T01_modulation_type ) // Is using OFDM
			{
				if( CURRENT_PROTECT_MECHANISM ) // Is using protect
					CTS_on = true; // Using CTS
			}
		}
	}

	if( RTS_on || CTS_on )
	{
		if( pT01->T01_modulation_type) // Is using OFDM
		{
			//CTS duration
			// 2 SIFS + DATA transmit time + 1 ACK
			// ACK Rate : 24 Mega bps
			// ACK frame length = 14 bytes
			Duration = 2*DEFAULT_SIFSTIME +
					   2*PREAMBLE_PLUS_SIGNAL_PLUS_SIGNALEXTENSION +
					   ((BodyLen*8 + 22 + Rate*4 - 1)/(Rate*4))*Tsym +
					   ((112 + 22 + 95)/96)*Tsym;
		}
		else	//DSSS
		{
			//CTS duration
			// 2 SIFS + DATA transmit time + 1 ACK
			// Rate : ?? Mega bps
			// ACK frame length = 14 bytes
			if( pT01->T01_plcp_header_length ) //long preamble
				Duration = LONG_PREAMBLE_PLUS_PLCPHEADER_TIME*2;
			else
				Duration = SHORT_PREAMBLE_PLUS_PLCPHEADER_TIME*2;

			Duration += ( ((BodyLen + 14)*8 + Rate-1) / Rate +
						DEFAULT_SIFSTIME*2 );
		}

		if( RTS_on )
		{
			if( pT01->T01_modulation_type ) // Is using OFDM
			{
				//CTS + 1 SIFS + CTS duration
				//CTS Rate : 24 Mega bps
				//CTS frame length = 14 bytes
				Duration += (DEFAULT_SIFSTIME +
								PREAMBLE_PLUS_SIGNAL_PLUS_SIGNALEXTENSION +
								((112 + 22 + 95)/96)*Tsym);
			}
			else
			{
				//CTS + 1 SIFS + CTS duration
				//CTS Rate : ?? Mega bps
				//CTS frame length = 14 bytes
				if( pT01->T01_plcp_header_length ) //long preamble
					Duration += LONG_PREAMBLE_PLUS_PLCPHEADER_TIME;
				else
					Duration += SHORT_PREAMBLE_PLUS_PLCPHEADER_TIME;

				Duration += ( ((112 + Rate-1) / Rate) + DEFAULT_SIFSTIME );
			}
		}

		// Set the value into USB descriptor
		pT01->T01_add_rts = RTS_on ? 1 : 0;
		pT01->T01_add_cts = CTS_on ? 1 : 0;
		pT01->T01_rts_cts_duration = Duration;
	}

	//=====================================
	// Fill the more fragment descriptor
	//=====================================
	if( boGroupAddr )
		Duration = 0;
	else
	{
		for( i=pDes->FragmentCount-1; i>0; i-- )
		{
			NextBodyLen = (u16)pNextT00->T00_frame_length;
			NextBodyLen += 4;	//CRC

			if( pT01->T01_modulation_type )
			{
				//OFDM
				// data transmit time + 3 SIFS + 2 ACK
				// Rate : ??Mega bps
				// ACK frame length = 14 bytes, tx rate = 24M
				Duration = PREAMBLE_PLUS_SIGNAL_PLUS_SIGNALEXTENSION * 3;
				Duration += (((NextBodyLen*8 + 22 + Rate*4 - 1)/(Rate*4)) * Tsym +
							(((2*14)*8 + 22 + 95)/96)*Tsym +
							DEFAULT_SIFSTIME*3);
			}
			else
			{
				//DSSS
				// data transmit time + 2 ACK + 3 SIFS
				// Rate : ??Mega bps
				// ACK frame length = 14 bytes
				//TODO :
				if( pT01->T01_plcp_header_length ) //long preamble
					Duration = LONG_PREAMBLE_PLUS_PLCPHEADER_TIME*3;
				else
					Duration = SHORT_PREAMBLE_PLUS_PLCPHEADER_TIME*3;

				Duration += ( ((NextBodyLen + (2*14))*8 + Rate-1) / Rate +
							DEFAULT_SIFSTIME*3 );
			}

			((u16 *)buffer)[5] = cpu_to_le16(Duration);// 4 USHOR for skip 8B USB, 2USHORT=FC + Duration

			//----20061009 add by anson's endian
			pNextT00->value = cpu_to_le32(pNextT00->value);
			pT01->value = cpu_to_le32( pT01->value );
			//----end 20061009 add by anson's endian

			buffer += OffsetSize;
			pT01 = (PT01_DESCRIPTOR)(buffer+4);
			if (i != 1)	//The last fragment will not have the next fragment
				pNextT00 = (PT00_DESCRIPTOR)(buffer+OffsetSize);
		}

		//=====================================
		// Fill the last fragment descriptor
		//=====================================
		if( pT01->T01_modulation_type )
		{
			//OFDM
			// 1 SIFS + 1 ACK
			// Rate : 24 Mega bps
			// ACK frame length = 14 bytes
			Duration = PREAMBLE_PLUS_SIGNAL_PLUS_SIGNALEXTENSION;
			//The Tx rate of ACK use 24M
			Duration += (((112 + 22 + 95)/96)*Tsym + DEFAULT_SIFSTIME );
		}
		else
		{
			// DSSS
			// 1 ACK + 1 SIFS
			// Rate : ?? Mega bps
			// ACK frame length = 14 bytes(112 bits)
			if( pT01->T01_plcp_header_length ) //long preamble
				Duration = LONG_PREAMBLE_PLUS_PLCPHEADER_TIME;
			else
				Duration = SHORT_PREAMBLE_PLUS_PLCPHEADER_TIME;

			Duration += ( (112 + Rate-1)/Rate +	DEFAULT_SIFSTIME );
		}
	}

	((u16 *)buffer)[5] = cpu_to_le16(Duration);// 4 USHOR for skip 8B USB, 2USHORT=FC + Duration
	pT00->value = cpu_to_le32(pT00->value);
	pT01->value = cpu_to_le32(pT01->value);
	//--end 20061009 add

}