#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tw; int th; struct TYPE_5__* tcps; struct TYPE_5__* tccps; struct TYPE_5__* matrice; struct TYPE_5__* comment; struct TYPE_5__* cp; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  TYPE_1__ opj_cp_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

void j2k_destroy_compress(opj_j2k_t *j2k) {
	int tileno;

	if(!j2k) return;
	if(j2k->cp != NULL) {
		opj_cp_t *cp = j2k->cp;

		if(cp->comment) {
			opj_free(cp->comment);
		}
		if(cp->matrice) {
			opj_free(cp->matrice);
		}
		for (tileno = 0; tileno < cp->tw * cp->th; tileno++) {
			opj_free(cp->tcps[tileno].tccps);
		}
		opj_free(cp->tcps);
		opj_free(cp);
	}

	opj_free(j2k);
}