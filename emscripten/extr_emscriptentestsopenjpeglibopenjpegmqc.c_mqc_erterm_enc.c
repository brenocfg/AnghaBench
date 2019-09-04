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
struct TYPE_4__ {int ct; int c; int* bp; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_byteout (TYPE_1__*) ; 

void mqc_erterm_enc(opj_mqc_t *mqc) {
	int k = 11 - mqc->ct + 1;
	
	while (k > 0) {
		mqc->c <<= mqc->ct;
		mqc->ct = 0;
		mqc_byteout(mqc);
		k -= mqc->ct;
	}
	
	if (*mqc->bp != 0xff) {
		mqc_byteout(mqc);
	}
}