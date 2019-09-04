#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* tccps; } ;
typedef  TYPE_3__ opj_tcp_t ;
struct TYPE_10__ {TYPE_1__* image; int /*<<< orphan*/ * cio; TYPE_5__* cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_11__ {TYPE_3__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {int roishift; } ;
struct TYPE_7__ {int numcomps; } ;

/* Variables and functions */
 int J2K_MS_RGN ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_rgn(opj_j2k_t *j2k, int compno, int tileno) {
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = &cp->tcps[tileno];
	opj_cio_t *cio = j2k->cio;
	int numcomps = j2k->image->numcomps;
	
	cio_write(cio, J2K_MS_RGN, 2);						/* RGN  */
	cio_write(cio, numcomps <= 256 ? 5 : 6, 2);			/* Lrgn */
	cio_write(cio, compno, numcomps <= 256 ? 1 : 2);	/* Crgn */
	cio_write(cio, 0, 1);								/* Srgn */
	cio_write(cio, tcp->tccps[compno].roishift, 1);		/* SPrgn */
}