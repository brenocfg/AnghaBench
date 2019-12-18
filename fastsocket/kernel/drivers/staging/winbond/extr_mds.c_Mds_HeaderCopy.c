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
typedef  int /*<<< orphan*/  u16 ;
struct wb35_mds {int** TxRate; } ;
struct wbsoft_priv {struct wb35_mds Mds; } ;
struct wb35_descriptor {int** buffer_address; size_t Descriptor_ID; int TxRate; int /*<<< orphan*/  PreambleMode; int /*<<< orphan*/  FragmentThreshold; int /*<<< orphan*/  buffer_total_size; int /*<<< orphan*/ * buffer_size; } ;
struct TYPE_4__ {size_t T00_tx_packet_id; int T00_header_length; scalar_t__ value; } ;
struct TYPE_3__ {int T01_retry_abort_ebable; int T01_modulation_type; int T01_transmit_rate; int T01_fall_back_rate; int /*<<< orphan*/  T01_plcp_header_length; scalar_t__ T01_wep_id; scalar_t__ value; } ;
typedef  TYPE_1__* PT01_DESCRIPTOR ;
typedef  TYPE_2__* PT00_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_FRAGMENT_THRESHOLD ; 
 int /*<<< orphan*/  CURRENT_PREAMBLE_MODE ; 
 int CURRENT_TX_RATE_FOR_MNG ; 
 int /*<<< orphan*/  DEFAULT_FRAGMENT_THRESHOLD ; 
 int DOT_11_MAC_HEADER_SIZE ; 
 int /*<<< orphan*/  WLAN_PREAMBLE_TYPE_LONG ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static void Mds_HeaderCopy(struct wbsoft_priv * adapter, struct wb35_descriptor *pDes, u8 *TargetBuffer)
{
	struct wb35_mds *pMds = &adapter->Mds;
	u8	*src_buffer = pDes->buffer_address[0];//931130.5.g
	PT00_DESCRIPTOR	pT00;
	PT01_DESCRIPTOR	pT01;
	u16	stmp;
	u8	i, ctmp1, ctmp2, ctmpf;
	u16	FragmentThreshold = CURRENT_FRAGMENT_THRESHOLD;


	stmp = pDes->buffer_total_size;
	//
	// Set USB header 8 byte
	//
	pT00 = (PT00_DESCRIPTOR)TargetBuffer;
	TargetBuffer += 4;
	pT01 = (PT01_DESCRIPTOR)TargetBuffer;
	TargetBuffer += 4;

	pT00->value = 0;// Clear
	pT01->value = 0;// Clear

	pT00->T00_tx_packet_id = pDes->Descriptor_ID;// Set packet ID
	pT00->T00_header_length = 24;// Set header length
	pT01->T01_retry_abort_ebable = 1;//921013 931130.5.h

	// Key ID setup
	pT01->T01_wep_id = 0;

	FragmentThreshold = DEFAULT_FRAGMENT_THRESHOLD;	//Do not fragment
	// Copy full data, the 1'st buffer contain all the data 931130.5.j
	memcpy( TargetBuffer, src_buffer, DOT_11_MAC_HEADER_SIZE );// Copy header
	pDes->buffer_address[0] = src_buffer + DOT_11_MAC_HEADER_SIZE;
	pDes->buffer_total_size -= DOT_11_MAC_HEADER_SIZE;
	pDes->buffer_size[0] = pDes->buffer_total_size;

	// Set fragment threshold
	FragmentThreshold -= (DOT_11_MAC_HEADER_SIZE + 4);
	pDes->FragmentThreshold = FragmentThreshold;

	// Set more frag bit
	TargetBuffer[1] |= 0x04;// Set more frag bit

	//
	// Set tx rate
	//
	stmp = *(u16 *)(TargetBuffer+30); // 2n alignment address

	//Use basic rate
	ctmp1 = ctmpf = CURRENT_TX_RATE_FOR_MNG;

	pDes->TxRate = ctmp1;
	#ifdef _PE_TX_DUMP_
	printk("Tx rate =%x\n", ctmp1);
	#endif

	pT01->T01_modulation_type = (ctmp1%3) ? 0 : 1;

	for( i=0; i<2; i++ ) {
		if( i == 1 )
			ctmp1 = ctmpf;

		pMds->TxRate[pDes->Descriptor_ID][i] = ctmp1; // backup the ta rate and fall back rate

		if( ctmp1 == 108) ctmp2 = 7;
		else if( ctmp1 == 96 ) ctmp2 = 6; // Rate convert for USB
		else if( ctmp1 == 72 ) ctmp2 = 5;
		else if( ctmp1 == 48 ) ctmp2 = 4;
		else if( ctmp1 == 36 ) ctmp2 = 3;
		else if( ctmp1 == 24 ) ctmp2 = 2;
		else if( ctmp1 == 18 ) ctmp2 = 1;
		else if( ctmp1 == 12 ) ctmp2 = 0;
		else if( ctmp1 == 22 ) ctmp2 = 3;
		else if( ctmp1 == 11 ) ctmp2 = 2;
		else if( ctmp1 == 4  ) ctmp2 = 1;
		else ctmp2 = 0; // if( ctmp1 == 2  ) or default

		if( i == 0 )
			pT01->T01_transmit_rate = ctmp2;
		else
			pT01->T01_fall_back_rate = ctmp2;
	}

	//
	// Set preamble type
	//
	if ((pT01->T01_modulation_type == 0) && (pT01->T01_transmit_rate == 0))	// RATE_1M
		pDes->PreambleMode =  WLAN_PREAMBLE_TYPE_LONG;
	else
		pDes->PreambleMode =  CURRENT_PREAMBLE_MODE;
	pT01->T01_plcp_header_length = pDes->PreambleMode;	// Set preamble

}