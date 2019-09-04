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
struct TYPE_3__ {int bp; int start; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */

int mqc_numbytes(opj_mqc_t *mqc) {
	return mqc->bp - mqc->start;
}