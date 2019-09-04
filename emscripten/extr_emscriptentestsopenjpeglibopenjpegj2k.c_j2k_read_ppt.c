#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ppt; unsigned char* ppt_data; unsigned char* ppt_data_first; int ppt_store; int ppt_len; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_6__ {int curtileno; int /*<<< orphan*/ * cio; TYPE_3__* cp; } ;
typedef  TYPE_2__ opj_j2k_t ;
struct TYPE_7__ {TYPE_1__* tcps; } ;
typedef  TYPE_3__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opj_malloc (int) ; 
 scalar_t__ opj_realloc (unsigned char*,int) ; 

__attribute__((used)) static void j2k_read_ppt(opj_j2k_t *j2k) {
	int len, Z_ppt, i, j = 0;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = cp->tcps + j2k->curtileno;
	opj_cio_t *cio = j2k->cio;

	len = cio_read(cio, 2);
	Z_ppt = cio_read(cio, 1);
	tcp->ppt = 1;
	if (Z_ppt == 0) {		/* First PPT marker */
		tcp->ppt_data = (unsigned char *) opj_malloc((len - 3) * sizeof(unsigned char));
		tcp->ppt_data_first = tcp->ppt_data;
		tcp->ppt_store = 0;
		tcp->ppt_len = len - 3;
	} else {			/* NON-first PPT marker */
		tcp->ppt_data =	(unsigned char *) opj_realloc(tcp->ppt_data, (len - 3 + tcp->ppt_store) * sizeof(unsigned char));
		tcp->ppt_data_first = tcp->ppt_data;
		tcp->ppt_len = len - 3 + tcp->ppt_store;
	}
	j = tcp->ppt_store;
	for (i = len - 3; i > 0; i--) {
		tcp->ppt_data[j] = cio_read(cio, 1);
		j++;
	}
	tcp->ppt_store = j;
}