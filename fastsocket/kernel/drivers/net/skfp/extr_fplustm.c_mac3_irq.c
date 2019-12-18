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
typedef  int u_short ;
struct TYPE_3__ {int /*<<< orphan*/  mac_r_restart_counter; } ;
struct TYPE_4__ {TYPE_1__ mac_ct; } ;
struct s_smc {TYPE_2__ hw; } ;

/* Variables and functions */
 int FM_SRBFL2 ; 
 int FM_SRCVOVR2 ; 
 int FM_SRPERRQ1 ; 
 int FM_SRPERRQ2 ; 
 int /*<<< orphan*/  SMT_E0115 ; 
 int /*<<< orphan*/  SMT_E0115_MSG ; 
 int /*<<< orphan*/  SMT_E0116 ; 
 int /*<<< orphan*/  SMT_E0116_MSG ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  smt_stat_counter (struct s_smc*,int) ; 

void mac3_irq(struct s_smc *smc, u_short code_s3u, u_short code_s3l)
{
	UNUSED(code_s3l) ;

	if (code_s3u & (FM_SRCVOVR2 |	/* recv. FIFO overflow */
			FM_SRBFL2)) {	/* recv. buffer full */
		smc->hw.mac_ct.mac_r_restart_counter++ ;
		smt_stat_counter(smc,1);
	}


	if (code_s3u & FM_SRPERRQ2) {	/* parity error receive queue 2 */
		SMT_PANIC(smc,SMT_E0115, SMT_E0115_MSG) ;
	}
	if (code_s3u & FM_SRPERRQ1) {	/* parity error receive queue 2 */
		SMT_PANIC(smc,SMT_E0116, SMT_E0116_MSG) ;
	}
}