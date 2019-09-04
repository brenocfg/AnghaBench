#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* image; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_4__ {int numcomps; } ;

/* Variables and functions */
 int cio_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void j2k_read_crg(opj_j2k_t *j2k) {
	int len, i, Xcrg_i, Ycrg_i;
	
	opj_cio_t *cio = j2k->cio;
	int numcomps = j2k->image->numcomps;
	
	len = cio_read(cio, 2);			/* Lcrg */
	for (i = 0; i < numcomps; i++) {
		Xcrg_i = cio_read(cio, 2);	/* Xcrg_i */
		Ycrg_i = cio_read(cio, 2);	/* Ycrg_i */
	}
}