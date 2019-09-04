#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int csty; TYPE_1__* tccps; void* numlayers; scalar_t__ prg; void* mct; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_11__ {scalar_t__ state; size_t curtileno; TYPE_6__* cstr_info; TYPE_4__* image; TYPE_2__* default_tcp; TYPE_5__* cp; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_12__ {int numcomps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_13__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
struct TYPE_14__ {int* numdecompos; void* numlayers; scalar_t__ prog; } ;
typedef  TYPE_6__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_9__ {int csty; int numresolutions; } ;
typedef  scalar_t__ OPJ_PROG_ORDER ;

/* Variables and functions */
 int J2K_CP_CSTY_PRT ; 
 scalar_t__ J2K_STATE_TPH ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  j2k_read_cox (TYPE_3__*,int) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static void j2k_read_cod(opj_j2k_t *j2k) {
	int len, i, pos;
	
	opj_cio_t *cio = j2k->cio;
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_image_t *image = j2k->image;
	
	len = cio_read(cio, 2);				/* Lcod */
	tcp->csty = cio_read(cio, 1);		/* Scod */
	tcp->prg = (OPJ_PROG_ORDER)cio_read(cio, 1);		/* SGcod (A) */
	tcp->numlayers = cio_read(cio, 2);	/* SGcod (B) */
	tcp->mct = cio_read(cio, 1);		/* SGcod (C) */
	
	pos = cio_tell(cio);
	for (i = 0; i < image->numcomps; i++) {
		tcp->tccps[i].csty = tcp->csty & J2K_CP_CSTY_PRT;
		cio_seek(cio, pos);
		j2k_read_cox(j2k, i);
	}

	/* Index */
	if (j2k->cstr_info) {
		opj_codestream_info_t *cstr_info = j2k->cstr_info;
		cstr_info->prog = tcp->prg;
		cstr_info->numlayers = tcp->numlayers;
		cstr_info->numdecompos = (int*) opj_malloc(image->numcomps * sizeof(int));
		for (i = 0; i < image->numcomps; i++) {
			cstr_info->numdecompos[i] = tcp->tccps[i].numresolutions - 1;
		}
	}
}