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
struct TYPE_4__ {struct TYPE_4__* cl; struct TYPE_4__* comps; int /*<<< orphan*/  j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;

/* Variables and functions */
 int /*<<< orphan*/  j2k_destroy_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

void jp2_destroy_compress(opj_jp2_t *jp2) {
	if(jp2) {
		/* destroy the J2K codec */
		j2k_destroy_compress(jp2->j2k);

		if(jp2->comps) {
			opj_free(jp2->comps);
		}
		if(jp2->cl) {
			opj_free(jp2->cl);
		}
		opj_free(jp2);
	}
}