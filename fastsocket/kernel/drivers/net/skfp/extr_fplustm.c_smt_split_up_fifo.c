#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rx1_fifo_size; int fifo_config_mode; int tx_s_size; int tx_a0_size; int rx1_fifo_start; int rbc_ram_start; int tx_s_start; int tx_a0_start; int rx2_fifo_start; int rbc_ram_end; scalar_t__ rx2_fifo_size; } ;
struct TYPE_9__ {TYPE_3__ fifo; } ;
struct TYPE_10__ {TYPE_4__ fp; } ;
struct TYPE_7__ {int fddiESSSynchTxMode; TYPE_1__* a; } ;
struct s_smc {TYPE_5__ hw; TYPE_2__ mib; } ;
struct TYPE_6__ {scalar_t__ fddiPATHSbaPayload; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_SMT (char*,int,int) ; 
 size_t PATH0 ; 
 int RX_FIFO_OFF ; 
 scalar_t__ RX_FIFO_SPACE ; 
 int RX_LARGE_FIFO ; 
 scalar_t__ RX_SMALL_FIFO ; 
 int SEND_ASYNC_AS_SYNC ; 
 int /*<<< orphan*/  SMT_E0117 ; 
 int /*<<< orphan*/  SMT_E0117_MSG ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SMT_R1_RXD_COUNT ; 
 int SMT_R2_RXD_COUNT ; 
 int SYNC_TRAFFIC_ON ; 
 int TX_FIFO_SPACE ; 
 int TX_LARGE_FIFO ; 
 void* TX_MEDIUM_FIFO ; 
 int TX_SMALL_FIFO ; 

__attribute__((used)) static void smt_split_up_fifo(struct s_smc *smc)
{

/*
	BEGIN_MANUAL_ENTRY(module;mem;1)
	-------------------------------------------------------------
	RECEIVE BUFFER MEMORY DIVERSION
	-------------------------------------------------------------

	R1_RxD == SMT_R1_RXD_COUNT
	R2_RxD == SMT_R2_RXD_COUNT

	SMT_R1_RXD_COUNT must be unequal zero

		   | R1_RxD R2_RxD |R1_RxD R2_RxD | R1_RxD R2_RxD
		   |   x      0	   |  x	    1-3	  |   x     < 3
	----------------------------------------------------------------------
		   |   63,75 kB	   |    54,75	  |	R1_RxD
	rx queue 1 | RX_FIFO_SPACE | RX_LARGE_FIFO| ------------- * 63,75 kB
		   |		   |		  | R1_RxD+R2_RxD
	----------------------------------------------------------------------
		   |		   |    9 kB	  |     R2_RxD
	rx queue 2 |	0 kB	   | RX_SMALL_FIFO| ------------- * 63,75 kB
		   |  (not used)   |		  | R1_RxD+R2_RxD

	END_MANUAL_ENTRY
*/

	if (SMT_R1_RXD_COUNT == 0) {
		SMT_PANIC(smc,SMT_E0117, SMT_E0117_MSG) ;
	}

	switch(SMT_R2_RXD_COUNT) {
	case 0:
		smc->hw.fp.fifo.rx1_fifo_size = RX_FIFO_SPACE ;
		smc->hw.fp.fifo.rx2_fifo_size = 0 ;
		break ;
	case 1:
	case 2:
	case 3:
		smc->hw.fp.fifo.rx1_fifo_size = RX_LARGE_FIFO ;
		smc->hw.fp.fifo.rx2_fifo_size = RX_SMALL_FIFO ;
		break ;
	default:	/* this is not the real defaule */
		smc->hw.fp.fifo.rx1_fifo_size = RX_FIFO_SPACE *
		SMT_R1_RXD_COUNT/(SMT_R1_RXD_COUNT+SMT_R2_RXD_COUNT) ;
		smc->hw.fp.fifo.rx2_fifo_size = RX_FIFO_SPACE *
		SMT_R2_RXD_COUNT/(SMT_R1_RXD_COUNT+SMT_R2_RXD_COUNT) ;
		break ;
	}

/*
	BEGIN_MANUAL_ENTRY(module;mem;1)
	-------------------------------------------------------------
	TRANSMIT BUFFER MEMORY DIVERSION
	-------------------------------------------------------------


		 | no sync bw	| sync bw available and | sync bw available and
		 | available	| SynchTxMode = SPLIT	| SynchTxMode = ALL
	-----------------------------------------------------------------------
	sync tx	 |     0 kB	|	32 kB		|	55 kB
	queue	 |		|   TX_MEDIUM_FIFO	|   TX_LARGE_FIFO
	-----------------------------------------------------------------------
	async tx |    64 kB	|	32 kB		|	 9 k
	queue	 | TX_FIFO_SPACE|   TX_MEDIUM_FIFO	|   TX_SMALL_FIFO

	END_MANUAL_ENTRY
*/

	/*
	 * set the tx mode bits
	 */
	if (smc->mib.a[PATH0].fddiPATHSbaPayload) {
#ifdef ESS
		smc->hw.fp.fifo.fifo_config_mode |=
			smc->mib.fddiESSSynchTxMode | SYNC_TRAFFIC_ON ;
#endif
	}
	else {
		smc->hw.fp.fifo.fifo_config_mode &=
			~(SEND_ASYNC_AS_SYNC|SYNC_TRAFFIC_ON) ;
	}

	/*
	 * split up the FIFO
	 */
	if (smc->hw.fp.fifo.fifo_config_mode & SYNC_TRAFFIC_ON) {
		if (smc->hw.fp.fifo.fifo_config_mode & SEND_ASYNC_AS_SYNC) {
			smc->hw.fp.fifo.tx_s_size = TX_LARGE_FIFO ;
			smc->hw.fp.fifo.tx_a0_size = TX_SMALL_FIFO ;
		}
		else {
			smc->hw.fp.fifo.tx_s_size = TX_MEDIUM_FIFO ;
			smc->hw.fp.fifo.tx_a0_size = TX_MEDIUM_FIFO ;
		}
	}
	else {
			smc->hw.fp.fifo.tx_s_size = 0 ;
			smc->hw.fp.fifo.tx_a0_size = TX_FIFO_SPACE ;
	}

	smc->hw.fp.fifo.rx1_fifo_start = smc->hw.fp.fifo.rbc_ram_start +
		RX_FIFO_OFF ;
	smc->hw.fp.fifo.tx_s_start = smc->hw.fp.fifo.rx1_fifo_start +
		smc->hw.fp.fifo.rx1_fifo_size ;
	smc->hw.fp.fifo.tx_a0_start = smc->hw.fp.fifo.tx_s_start +
		smc->hw.fp.fifo.tx_s_size ;
	smc->hw.fp.fifo.rx2_fifo_start = smc->hw.fp.fifo.tx_a0_start +
		smc->hw.fp.fifo.tx_a0_size ;

	DB_SMT("FIFO split: mode = %x\n",smc->hw.fp.fifo.fifo_config_mode,0) ;
	DB_SMT("rbc_ram_start =	%x	 rbc_ram_end = 	%x\n",
		smc->hw.fp.fifo.rbc_ram_start, smc->hw.fp.fifo.rbc_ram_end) ;
	DB_SMT("rx1_fifo_start = %x	 tx_s_start = 	%x\n",
		smc->hw.fp.fifo.rx1_fifo_start, smc->hw.fp.fifo.tx_s_start) ;
	DB_SMT("tx_a0_start =	%x	 rx2_fifo_start = 	%x\n",
		smc->hw.fp.fifo.tx_a0_start, smc->hw.fp.fifo.rx2_fifo_start) ;
}