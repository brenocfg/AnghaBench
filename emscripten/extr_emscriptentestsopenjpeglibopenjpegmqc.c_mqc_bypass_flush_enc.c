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
struct TYPE_3__ {unsigned char ct; scalar_t__ c; scalar_t__* bp; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */

int mqc_bypass_flush_enc(opj_mqc_t *mqc) {
	unsigned char bit_padding;
	
	bit_padding = 0;
	
	if (mqc->ct != 0) {
		while (mqc->ct > 0) {
			mqc->ct--;
			mqc->c += bit_padding << mqc->ct;
			bit_padding = (bit_padding + 1) & 0x01;
		}
		mqc->bp++;
		*mqc->bp = mqc->c;
		mqc->ct = 8;
		mqc->c = 0;
	}
	
	return 1;
}