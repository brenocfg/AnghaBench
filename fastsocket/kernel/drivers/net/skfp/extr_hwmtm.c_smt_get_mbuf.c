#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* mb_free; } ;
struct TYPE_8__ {TYPE_1__ mbuf_pool; } ;
struct TYPE_9__ {TYPE_2__ hwm; } ;
struct s_smc {TYPE_3__ os; } ;
struct TYPE_10__ {int sm_off; int sm_use_count; struct TYPE_10__* sm_next; } ;
typedef  TYPE_4__ SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DB_GEN (char*,void*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* mb_free ; 

SMbuf *smt_get_mbuf(struct s_smc *smc)
{
	register SMbuf	*mb ;

#ifndef	COMMON_MB_POOL
	mb = smc->os.hwm.mbuf_pool.mb_free ;
#else
	mb = mb_free ;
#endif
	if (mb) {
#ifndef	COMMON_MB_POOL
		smc->os.hwm.mbuf_pool.mb_free = mb->sm_next ;
#else
		mb_free = mb->sm_next ;
#endif
		mb->sm_off = 8 ;
		mb->sm_use_count = 1 ;
	}
	DB_GEN("get SMbuf: mb = %x",(void *)mb,0,3) ;
	return (mb) ;	/* May be NULL */
}