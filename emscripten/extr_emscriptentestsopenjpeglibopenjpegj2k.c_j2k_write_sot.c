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
struct TYPE_3__ {int sot_start; int curtileno; int cur_tp_num; int* cur_totnum_tp; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int J2K_MS_SOT ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_sot(opj_j2k_t *j2k) {
	int lenp, len;

	opj_cio_t *cio = j2k->cio;

	j2k->sot_start = cio_tell(cio);
	cio_write(cio, J2K_MS_SOT, 2);		/* SOT */
	lenp = cio_tell(cio);
	cio_skip(cio, 2);					/* Lsot (further) */
	cio_write(cio, j2k->curtileno, 2);	/* Isot */
	cio_skip(cio, 4);					/* Psot (further in j2k_write_sod) */
	cio_write(cio, j2k->cur_tp_num , 1);	/* TPsot */
	cio_write(cio, j2k->cur_totnum_tp[j2k->curtileno], 1);		/* TNsot */
	len = cio_tell(cio) - lenp;
	cio_seek(cio, lenp);
	cio_write(cio, len, 2);				/* Lsot */
	cio_seek(cio, lenp + len);

	/* UniPG>> */
#ifdef USE_JPWL
	/* update markers struct */
	j2k_add_marker(j2k->cstr_info, J2K_MS_SOT, j2k->sot_start, len + 2);
#endif /* USE_JPWL */
	/* <<UniPG */
}