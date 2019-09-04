#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ct; int c; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_byteout (TYPE_1__*) ; 

int mqc_restart_enc(opj_mqc_t *mqc) {
	int correction = 1;
	
	/* <flush part> */
	int n = 27 - 15 - mqc->ct;
	mqc->c <<= mqc->ct;
	while (n > 0) {
		mqc_byteout(mqc);
		n -= mqc->ct;
		mqc->c <<= mqc->ct;
	}
	mqc_byteout(mqc);
	
	return correction;
}