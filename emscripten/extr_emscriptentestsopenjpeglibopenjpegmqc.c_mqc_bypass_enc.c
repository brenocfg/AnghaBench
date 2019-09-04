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
struct TYPE_3__ {int ct; int c; int* bp; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */

void mqc_bypass_enc(opj_mqc_t *mqc, int d) {
	mqc->ct--;
	mqc->c = mqc->c + (d << mqc->ct);
	if (mqc->ct == 0) {
		mqc->bp++;
		*mqc->bp = mqc->c;
		mqc->ct = 8;
		if (*mqc->bp == 0xff) {
			mqc->ct = 7;
		}
		mqc->c = 0;
	}
}