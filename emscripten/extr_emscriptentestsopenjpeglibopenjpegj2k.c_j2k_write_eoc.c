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
 int /*<<< orphan*/  J2K_MS_EOC ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void j2k_write_eoc(opj_j2k_t *j2k) {
	opj_cio_t *cio = j2k->cio;
	/* opj_event_msg(j2k->cinfo, "%.8x: EOC\n", cio_tell(cio) + j2k->pos_correction); */
	cio_write(cio, J2K_MS_EOC, 2);

/* UniPG>> */
#ifdef USE_JPWL
	/* update markers struct */
	j2k_add_marker(j2k->cstr_info, J2K_MS_EOC, cio_tell(cio) - 2, 2);
#endif /* USE_JPWL */
/* <<UniPG */
}