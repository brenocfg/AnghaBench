#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int csty; int prg; int numlayers; int mct; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_7__ {size_t curtileno; TYPE_3__* cp; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_2__ opj_j2k_t ;
struct TYPE_8__ {TYPE_1__* tcps; } ;
typedef  TYPE_3__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int J2K_MS_COD ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  j2k_write_cox (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j2k_write_cod(opj_j2k_t *j2k) {
	opj_cp_t *cp = NULL;
	opj_tcp_t *tcp = NULL;
	int lenp, len;

	opj_cio_t *cio = j2k->cio;
	
	cio_write(cio, J2K_MS_COD, 2);	/* COD */
	
	lenp = cio_tell(cio);
	cio_skip(cio, 2);
	
	cp = j2k->cp;
	tcp = &cp->tcps[j2k->curtileno];

	cio_write(cio, tcp->csty, 1);		/* Scod */
	cio_write(cio, tcp->prg, 1);		/* SGcod (A) */
	cio_write(cio, tcp->numlayers, 2);	/* SGcod (B) */
	cio_write(cio, tcp->mct, 1);		/* SGcod (C) */
	
	j2k_write_cox(j2k, 0);
	len = cio_tell(cio) - lenp;
	cio_seek(cio, lenp);
	cio_write(cio, len, 2);		/* Lcod */
	cio_seek(cio, lenp + len);
}