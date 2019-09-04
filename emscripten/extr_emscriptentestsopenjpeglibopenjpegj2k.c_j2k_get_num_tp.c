#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pocs; int /*<<< orphan*/  prg; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_7__ {int tp_on; char tp_flag; int tp_pos; TYPE_2__* tcps; } ;
typedef  TYPE_3__ opj_cp_t ;
struct TYPE_5__ {int compE; int resE; int prcE; int layE; } ;

/* Variables and functions */
 char* j2k_convert_progression_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int j2k_get_num_tp(opj_cp_t *cp,int pino,int tileno){
	char *prog;
	int i;
	int tpnum=1,tpend=0;
	opj_tcp_t *tcp = &cp->tcps[tileno];
	prog = j2k_convert_progression_order(tcp->prg);
	
	if(cp->tp_on == 1){
		for(i=0;i<4;i++){
			if(tpend!=1){
				if( cp->tp_flag == prog[i] ){
					tpend=1;cp->tp_pos=i;
				}
				switch(prog[i]){
				case 'C':
					tpnum= tpnum * tcp->pocs[pino].compE;
					break;
				case 'R':
					tpnum= tpnum * tcp->pocs[pino].resE;
					break;
				case 'P':
					tpnum= tpnum * tcp->pocs[pino].prcE;
					break;
				case 'L':
					tpnum= tpnum * tcp->pocs[pino].layE;
					break;
				}
			}
		}
	}else{
		tpnum=1;
	}
	return tpnum;
}