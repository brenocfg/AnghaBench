#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_encode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mqc_setcurctx (int /*<<< orphan*/ *,int) ; 

void mqc_segmark_enc(opj_mqc_t *mqc) {
	int i;
	mqc_setcurctx(mqc, 18);
	
	for (i = 1; i < 5; i++) {
		mqc_encode(mqc, i % 2);
	}
}