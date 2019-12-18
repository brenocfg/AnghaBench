#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union s_fp_descr {int dummy; } s_fp_descr ;
typedef  int u_int ;
struct s_smt_fp_txd {int dummy; } ;
struct s_smt_fp_rxd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mb_start; int /*<<< orphan*/ * mb; } ;
struct TYPE_5__ {TYPE_1__ mbuf_pool; union s_fp_descr volatile* descr_p; } ;
struct TYPE_6__ {TYPE_2__ hwm; } ;
struct s_smc {TYPE_3__ os; } ;
typedef  int /*<<< orphan*/  SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  HWM_E0001 ; 
 int /*<<< orphan*/  HWM_E0001_MSG ; 
 int /*<<< orphan*/  HWM_E0002 ; 
 int /*<<< orphan*/  HWM_E0002_MSG ; 
 int MAX_MBUF ; 
 scalar_t__ RXD_TXD_COUNT ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mac_drv_get_desc_mem (struct s_smc*,int) ; 
 scalar_t__ mac_drv_get_space (struct s_smc*,int) ; 
 int /*<<< orphan*/ * mb_start ; 

int mac_drv_init(struct s_smc *smc)
{
	if (sizeof(struct s_smt_fp_rxd) % 16) {
		SMT_PANIC(smc,HWM_E0001,HWM_E0001_MSG) ;
	}
	if (sizeof(struct s_smt_fp_txd) % 16) {
		SMT_PANIC(smc,HWM_E0002,HWM_E0002_MSG) ;
	}

	/*
	 * get the required memory for the RxDs and TxDs
	 */
	if (!(smc->os.hwm.descr_p = (union s_fp_descr volatile *)
		mac_drv_get_desc_mem(smc,(u_int)
		(RXD_TXD_COUNT+1)*sizeof(struct s_smt_fp_txd)))) {
		return(1) ;	/* no space the hwm modul can't work */
	}

	/*
	 * get the memory for the SMT MBufs
	 */
#ifndef	MB_OUTSIDE_SMC
	smc->os.hwm.mbuf_pool.mb_start=(SMbuf *)(&smc->os.hwm.mbuf_pool.mb[0]) ;
#else
#ifndef	COMMON_MB_POOL
	if (!(smc->os.hwm.mbuf_pool.mb_start = (SMbuf *) mac_drv_get_space(smc,
		MAX_MBUF*sizeof(SMbuf)))) {
		return(1) ;	/* no space the hwm modul can't work */
	}
#else
	if (!mb_start) {
		if (!(mb_start = (SMbuf *) mac_drv_get_space(smc,
			MAX_MBUF*sizeof(SMbuf)))) {
			return(1) ;	/* no space the hwm modul can't work */
		}
	}
#endif
#endif
	return (0) ;
}