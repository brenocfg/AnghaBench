#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* image; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_1__ opj_j2k_t ;
struct TYPE_6__ {int numcomps; } ;
typedef  TYPE_2__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  j2k_read_qcx (TYPE_1__*,int,int) ; 

__attribute__((used)) static void j2k_read_qcd(opj_j2k_t *j2k) {
	int len, i, pos;

	opj_cio_t *cio = j2k->cio;
	opj_image_t *image = j2k->image;
	
	len = cio_read(cio, 2);		/* Lqcd */
	pos = cio_tell(cio);
	for (i = 0; i < image->numcomps; i++) {
		cio_seek(cio, pos);
		j2k_read_qcx(j2k, i, len - 2);
	}
}