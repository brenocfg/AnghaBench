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
struct TYPE_3__ {int totnum_tp; int /*<<< orphan*/  tlm_start; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int J2K_MS_TLM ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_tlm(opj_j2k_t *j2k){
	int lenp;
	opj_cio_t *cio = j2k->cio;
	j2k->tlm_start = cio_tell(cio);
	cio_write(cio, J2K_MS_TLM, 2);/* TLM */
	lenp = 4 + (5*j2k->totnum_tp);
	cio_write(cio,lenp,2);				/* Ltlm */
	cio_write(cio, 0,1);					/* Ztlm=0*/
	cio_write(cio,80,1);					/* Stlm ST=1(8bits-255 tiles max),SP=1(Ptlm=32bits) */
	cio_skip(cio,5*j2k->totnum_tp);
}