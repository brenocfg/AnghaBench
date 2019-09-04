#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enum_prog; char* str_prog; } ;
typedef  TYPE_1__ j2k_prog_order_t ;
typedef  int OPJ_PROG_ORDER ;

/* Variables and functions */
 TYPE_1__* j2k_prog_order_list ; 

char *j2k_convert_progression_order(OPJ_PROG_ORDER prg_order){
	j2k_prog_order_t *po;
	for(po = j2k_prog_order_list; po->enum_prog != -1; po++ ){
		if(po->enum_prog == prg_order){
			break;
		}
	}
	return po->str_prog;
}