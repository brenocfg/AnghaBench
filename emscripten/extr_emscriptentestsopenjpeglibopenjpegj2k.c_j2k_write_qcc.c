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
struct TYPE_6__ {TYPE_1__* image; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_2__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_5__ {int numcomps; } ;

/* Variables and functions */
 int J2K_MS_QCC ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,int) ; 
 int cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  j2k_write_qcx (TYPE_2__*,int) ; 

__attribute__((used)) static void j2k_write_qcc(opj_j2k_t *j2k, int compno) {
	int lenp, len;

	opj_cio_t *cio = j2k->cio;
	
	cio_write(cio, J2K_MS_QCC, 2);	/* QCC */
	lenp = cio_tell(cio);
	cio_skip(cio, 2);
	cio_write(cio, compno, j2k->image->numcomps <= 256 ? 1 : 2);	/* Cqcc */
	j2k_write_qcx(j2k, compno);
	len = cio_tell(cio) - lenp;
	cio_seek(cio, lenp);
	cio_write(cio, len, 2);			/* Lqcc */
	cio_seek(cio, lenp + len);
}