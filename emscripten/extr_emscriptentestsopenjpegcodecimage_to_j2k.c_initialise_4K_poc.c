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
struct TYPE_3__ {int tile; int resno0; int layno1; int resno1; int compno1; void* prg1; scalar_t__ compno0; } ;
typedef  TYPE_1__ opj_poc_t ;

/* Variables and functions */
 void* CPRL ; 

__attribute__((used)) static int initialise_4K_poc(opj_poc_t *POC, int numres){
	POC[0].tile  = 1;
	POC[0].resno0  = 0;
	POC[0].compno0 = 0;
	POC[0].layno1  = 1;
	POC[0].resno1  = numres-1;
	POC[0].compno1 = 3;
	POC[0].prg1 = CPRL;
	POC[1].tile  = 1;
	POC[1].resno0  = numres-1;
	POC[1].compno0 = 0;
	POC[1].layno1  = 1;
	POC[1].resno1  = numres;
	POC[1].compno1 = 3;
	POC[1].prg1 = CPRL;
	return 2;
}