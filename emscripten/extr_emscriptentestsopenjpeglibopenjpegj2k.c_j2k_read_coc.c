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
struct TYPE_10__ {scalar_t__ state; size_t curtileno; int /*<<< orphan*/ * cio; TYPE_4__* image; TYPE_2__* default_tcp; TYPE_5__* cp; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_11__ {int numcomps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_12__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {void* csty; } ;

/* Variables and functions */
 scalar_t__ J2K_STATE_TPH ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  j2k_read_cox (TYPE_3__*,int) ; 

__attribute__((used)) static void j2k_read_coc(opj_j2k_t *j2k) {
	int len, compno;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_image_t *image = j2k->image;
	opj_cio_t *cio = j2k->cio;
	
	len = cio_read(cio, 2);		/* Lcoc */
	compno = cio_read(cio, image->numcomps <= 256 ? 1 : 2);	/* Ccoc */
	tcp->tccps[compno].csty = cio_read(cio, 1);	/* Scoc */
	j2k_read_cox(j2k, compno);
}