#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tcd_image; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_tcd_t ;
typedef  int /*<<< orphan*/  opj_tcd_image_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 scalar_t__ opj_malloc (int) ; 

opj_tcd_t* tcd_create(opj_common_ptr cinfo) {
	/* create the tcd structure */
	opj_tcd_t *tcd = (opj_tcd_t*)opj_malloc(sizeof(opj_tcd_t));
	if(!tcd) return NULL;
	tcd->cinfo = cinfo;
	tcd->tcd_image = (opj_tcd_image_t*)opj_malloc(sizeof(opj_tcd_image_t));
	if(!tcd->tcd_image) {
		opj_free(tcd);
		return NULL;
	}

	return tcd;
}