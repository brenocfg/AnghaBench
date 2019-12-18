#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_6__* bristats; TYPE_3__* pristats; } ;
struct TYPE_19__ {unsigned long tx_good; unsigned long tx_bad; unsigned long rx_good; unsigned long rx_bad; } ;
struct TYPE_24__ {scalar_t__ modelid; TYPE_7__ status; TYPE_4__ dch_stats; scalar_t__ l2_status; scalar_t__ l1_status; int /*<<< orphan*/  proc_ver; int /*<<< orphan*/  load_ver; int /*<<< orphan*/  interface; int /*<<< orphan*/  ramsize; int /*<<< orphan*/  irq; int /*<<< orphan*/  rambase; int /*<<< orphan*/  iobase; int /*<<< orphan*/  part_no; int /*<<< orphan*/  serial_no; } ;
typedef  TYPE_9__ boardInfo ;
struct TYPE_23__ {scalar_t__* byte_array; } ;
struct TYPE_20__ {unsigned long tx_good; unsigned long tx_bad; unsigned long rx_good; unsigned long rx_bad; } ;
struct TYPE_21__ {int /*<<< orphan*/  dn; int /*<<< orphan*/  spid; TYPE_5__ link_stats; scalar_t__ call_type; scalar_t__ phy_stat; } ;
struct TYPE_17__ {unsigned long tx_good; unsigned long tx_bad; unsigned long rx_good; unsigned long rx_bad; } ;
struct TYPE_18__ {TYPE_2__ link_stats; scalar_t__ serv_state; scalar_t__ call_state; scalar_t__ call_type; scalar_t__ phy_stat; } ;
struct TYPE_16__ {int /*<<< orphan*/  st_u_sense; int /*<<< orphan*/  ram_size; scalar_t__* part_no; scalar_t__* serial_no; } ;
struct TYPE_15__ {scalar_t__ model; int nChannels; scalar_t__* proc_ver; scalar_t__* load_ver; TYPE_1__ hwconfig; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  rambase; int /*<<< orphan*/  iobase; } ;
struct TYPE_14__ {TYPE_8__ msg_data; } ;
typedef  TYPE_10__ RspMessage ;

/* Variables and functions */
 int BRI_CHANNELS ; 
 int /*<<< orphan*/  CEPID ; 
 scalar_t__ PRI_BOARD ; 
 int PRI_CHANNELS ; 
 int /*<<< orphan*/  SAR_TIMEOUT ; 
 int /*<<< orphan*/  ceReqCallGetCallType ; 
 int /*<<< orphan*/  ceReqCallGetMyNumber ; 
 int /*<<< orphan*/  ceReqCallGetSPID ; 
 int /*<<< orphan*/  ceReqClass0 ; 
 int /*<<< orphan*/  ceReqClass2 ; 
 int /*<<< orphan*/  ceReqLnkGetStats ; 
 int /*<<< orphan*/  ceReqPhyChCallState ; 
 int /*<<< orphan*/  ceReqPhyChServState ; 
 int /*<<< orphan*/  ceReqPhyStatus ; 
 int /*<<< orphan*/  ceReqTypeCall ; 
 int /*<<< orphan*/  ceReqTypeLnk ; 
 int /*<<< orphan*/  ceReqTypePhy ; 
 int /*<<< orphan*/  ceReqTypeStat ; 
 TYPE_12__** sc_adapter ; 
 int send_and_receive (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int GetStatus(int card, boardInfo *bi)
{
	RspMessage rcvmsg;
	int i, status;

	/*
	 * Fill in some of the basic info about the board
	 */
	bi->modelid = sc_adapter[card]->model;
	strcpy(bi->serial_no, sc_adapter[card]->hwconfig.serial_no);
	strcpy(bi->part_no, sc_adapter[card]->hwconfig.part_no);
	bi->iobase = sc_adapter[card]->iobase;
	bi->rambase = sc_adapter[card]->rambase;
	bi->irq = sc_adapter[card]->interrupt;
	bi->ramsize = sc_adapter[card]->hwconfig.ram_size;
	bi->interface = sc_adapter[card]->hwconfig.st_u_sense;
	strcpy(bi->load_ver, sc_adapter[card]->load_ver);
	strcpy(bi->proc_ver, sc_adapter[card]->proc_ver);

	/*
	 * Get the current PhyStats and LnkStats
	 */
	status = send_and_receive(card, CEPID, ceReqTypePhy, ceReqClass2,
		ceReqPhyStatus, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
	if(!status) {
		if(sc_adapter[card]->model < PRI_BOARD) {
			bi->l1_status = rcvmsg.msg_data.byte_array[2];
			for(i = 0 ; i < BRI_CHANNELS ; i++)
				bi->status.bristats[i].phy_stat =
					rcvmsg.msg_data.byte_array[i];
		}
		else {
			bi->l1_status = rcvmsg.msg_data.byte_array[0];
			bi->l2_status = rcvmsg.msg_data.byte_array[1];
			for(i = 0 ; i < PRI_CHANNELS ; i++)
				bi->status.pristats[i].phy_stat = 
					rcvmsg.msg_data.byte_array[i+2];
		}
	}
	
	/*
	 * Get the call types for each channel
	 */
	for (i = 0 ; i < sc_adapter[card]->nChannels ; i++) {
		status = send_and_receive(card, CEPID, ceReqTypeCall, ceReqClass0,
			ceReqCallGetCallType, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if(!status) {
			if (sc_adapter[card]->model == PRI_BOARD) {
				bi->status.pristats[i].call_type = 
					rcvmsg.msg_data.byte_array[0];
			}
			else {
				bi->status.bristats[i].call_type =
					rcvmsg.msg_data.byte_array[0];
			}
		}
	}
	
	/*
	 * If PRI, get the call states and service states for each channel
	 */
	if (sc_adapter[card]->model == PRI_BOARD) {
		/*
		 * Get the call states
		 */
		status = send_and_receive(card, CEPID, ceReqTypeStat, ceReqClass2,
			ceReqPhyChCallState, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if(!status) {
			for( i = 0 ; i < PRI_CHANNELS ; i++ )
				bi->status.pristats[i].call_state = 
					rcvmsg.msg_data.byte_array[i];
		}

		/*
		 * Get the service states
		 */
		status = send_and_receive(card, CEPID, ceReqTypeStat, ceReqClass2,
			ceReqPhyChServState, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if(!status) {
			for( i = 0 ; i < PRI_CHANNELS ; i++ )
				bi->status.pristats[i].serv_state = 
					rcvmsg.msg_data.byte_array[i];
		}

		/*
		 * Get the link stats for the channels
		 */
		for (i = 1 ; i <= PRI_CHANNELS ; i++) {
			status = send_and_receive(card, CEPID, ceReqTypeLnk, ceReqClass0,
				ceReqLnkGetStats, i, 0, NULL, &rcvmsg, SAR_TIMEOUT);
			if (!status) {
				bi->status.pristats[i-1].link_stats.tx_good =
					(unsigned long)rcvmsg.msg_data.byte_array[0];
				bi->status.pristats[i-1].link_stats.tx_bad =
					(unsigned long)rcvmsg.msg_data.byte_array[4];
				bi->status.pristats[i-1].link_stats.rx_good =
					(unsigned long)rcvmsg.msg_data.byte_array[8];
				bi->status.pristats[i-1].link_stats.rx_bad =
					(unsigned long)rcvmsg.msg_data.byte_array[12];
			}
		}

		/*
		 * Link stats for the D channel
		 */
		status = send_and_receive(card, CEPID, ceReqTypeLnk, ceReqClass0,
			ceReqLnkGetStats, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if (!status) {
			bi->dch_stats.tx_good = (unsigned long)rcvmsg.msg_data.byte_array[0];
			bi->dch_stats.tx_bad = (unsigned long)rcvmsg.msg_data.byte_array[4];
			bi->dch_stats.rx_good = (unsigned long)rcvmsg.msg_data.byte_array[8];
			bi->dch_stats.rx_bad = (unsigned long)rcvmsg.msg_data.byte_array[12];
		}

		return 0;
	}

	/*
	 * If BRI or POTS, Get SPID, DN and call types for each channel
	 */

	/*
	 * Get the link stats for the channels
	 */
	status = send_and_receive(card, CEPID, ceReqTypeLnk, ceReqClass0,
		ceReqLnkGetStats, 0, 0, NULL, &rcvmsg, SAR_TIMEOUT);
	if (!status) {
		bi->dch_stats.tx_good = (unsigned long)rcvmsg.msg_data.byte_array[0];
		bi->dch_stats.tx_bad = (unsigned long)rcvmsg.msg_data.byte_array[4];
		bi->dch_stats.rx_good = (unsigned long)rcvmsg.msg_data.byte_array[8];
		bi->dch_stats.rx_bad = (unsigned long)rcvmsg.msg_data.byte_array[12];
		bi->status.bristats[0].link_stats.tx_good = 
			(unsigned long)rcvmsg.msg_data.byte_array[16];
		bi->status.bristats[0].link_stats.tx_bad = 
			(unsigned long)rcvmsg.msg_data.byte_array[20];
		bi->status.bristats[0].link_stats.rx_good = 
			(unsigned long)rcvmsg.msg_data.byte_array[24];
		bi->status.bristats[0].link_stats.rx_bad = 
			(unsigned long)rcvmsg.msg_data.byte_array[28];
		bi->status.bristats[1].link_stats.tx_good = 
			(unsigned long)rcvmsg.msg_data.byte_array[32];
		bi->status.bristats[1].link_stats.tx_bad = 
			(unsigned long)rcvmsg.msg_data.byte_array[36];
		bi->status.bristats[1].link_stats.rx_good = 
			(unsigned long)rcvmsg.msg_data.byte_array[40];
		bi->status.bristats[1].link_stats.rx_bad = 
			(unsigned long)rcvmsg.msg_data.byte_array[44];
	}

	/*
	 * Get the SPIDs
	 */
	for (i = 0 ; i < BRI_CHANNELS ; i++) {
		status = send_and_receive(card, CEPID, ceReqTypeCall, ceReqClass0,
			ceReqCallGetSPID, i+1, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if (!status)
			strcpy(bi->status.bristats[i].spid, rcvmsg.msg_data.byte_array);
	}
		
	/*
	 * Get the DNs
	 */
	for (i = 0 ; i < BRI_CHANNELS ; i++) {
		status = send_and_receive(card, CEPID, ceReqTypeCall, ceReqClass0,
			ceReqCallGetMyNumber, i+1, 0, NULL, &rcvmsg, SAR_TIMEOUT);
		if (!status)
			strcpy(bi->status.bristats[i].dn, rcvmsg.msg_data.byte_array);
	}
		
	return 0;
}