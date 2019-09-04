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
struct TYPE_3__ {int /*<<< orphan*/ * cp; int /*<<< orphan*/ * image; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_t2_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
typedef  int /*<<< orphan*/  opj_cp_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;

/* Variables and functions */
 scalar_t__ opj_malloc (int) ; 

opj_t2_t* t2_create(opj_common_ptr cinfo, opj_image_t *image, opj_cp_t *cp) {
	/* create the tcd structure */
	opj_t2_t *t2 = (opj_t2_t*)opj_malloc(sizeof(opj_t2_t));
	if(!t2) return NULL;
	t2->cinfo = cinfo;
	t2->image = image;
	t2->cp = cp;

	return t2;
}