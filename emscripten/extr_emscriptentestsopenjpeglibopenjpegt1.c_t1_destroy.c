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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  raw; int /*<<< orphan*/  mqc; } ;
typedef  TYPE_1__ opj_t1_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_aligned_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  raw_destroy (int /*<<< orphan*/ ) ; 

void t1_destroy(opj_t1_t *t1) {
	if(t1) {
		/* destroy MQC and RAW handles */
		mqc_destroy(t1->mqc);
		raw_destroy(t1->raw);
		opj_aligned_free(t1->data);
		opj_aligned_free(t1->flags);
		opj_free(t1);
	}
}