#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* tcp; } ;
typedef  TYPE_2__ opj_tcd_t ;
struct TYPE_5__ {int numlayers; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcd_makelayer_fixed (TYPE_2__*,int,int) ; 

void tcd_rateallocate_fixed(opj_tcd_t *tcd) {
	int layno;
	for (layno = 0; layno < tcd->tcp->numlayers; layno++) {
		tcd_makelayer_fixed(tcd, layno, 1);
	}
}