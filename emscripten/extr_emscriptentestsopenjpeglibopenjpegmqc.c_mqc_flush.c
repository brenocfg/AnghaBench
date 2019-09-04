#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* bp; int /*<<< orphan*/  ct; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_byteout (TYPE_1__*) ; 
 int /*<<< orphan*/  mqc_setbits (TYPE_1__*) ; 

void mqc_flush(opj_mqc_t *mqc) {
	mqc_setbits(mqc);
	mqc->c <<= mqc->ct;
	mqc_byteout(mqc);
	mqc->c <<= mqc->ct;
	mqc_byteout(mqc);
	
	if (*mqc->bp != 0xff) {
		mqc->bp++;
	}
}