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
struct TYPE_3__ {int /*<<< orphan*/ * cio; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void j2k_read_tlm(opj_j2k_t *j2k) {
	int len, Ztlm, Stlm, ST, SP, tile_tlm, i;
	long int Ttlm_i, Ptlm_i;

	opj_cio_t *cio = j2k->cio;
	
	len = cio_read(cio, 2);		/* Ltlm */
	Ztlm = cio_read(cio, 1);	/* Ztlm */
	Stlm = cio_read(cio, 1);	/* Stlm */
	ST = ((Stlm >> 4) & 0x01) + ((Stlm >> 4) & 0x02);
	SP = (Stlm >> 6) & 0x01;
	tile_tlm = (len - 4) / ((SP + 1) * 2 + ST);
	for (i = 0; i < tile_tlm; i++) {
		Ttlm_i = cio_read(cio, ST);	/* Ttlm_i */
		Ptlm_i = cio_read(cio, SP ? 4 : 2);	/* Ptlm_i */
	}
}