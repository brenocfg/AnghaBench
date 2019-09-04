#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_10__ {size_t curtileno; int /*<<< orphan*/ * cio; TYPE_4__* image; TYPE_5__* cp; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_11__ {int numcomps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_12__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {int csty; } ;

/* Variables and functions */
 int J2K_MS_COC ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  j2k_write_cox (TYPE_3__*,int) ; 

__attribute__((used)) static void j2k_write_coc(opj_j2k_t *j2k, int compno) {
	int lenp, len;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = &cp->tcps[j2k->curtileno];
	opj_image_t *image = j2k->image;
	opj_cio_t *cio = j2k->cio;
	
	cio_write(cio, J2K_MS_COC, 2);	/* COC */
	lenp = cio_tell(cio);
	cio_skip(cio, 2);
	cio_write(cio, compno, image->numcomps <= 256 ? 1 : 2);	/* Ccoc */
	cio_write(cio, tcp->tccps[compno].csty, 1);	/* Scoc */
	j2k_write_cox(j2k, compno);
	len = cio_tell(cio) - lenp;
	cio_seek(cio, lenp);
	cio_write(cio, len, 2);			/* Lcoc */
	cio_seek(cio, lenp + len);
}