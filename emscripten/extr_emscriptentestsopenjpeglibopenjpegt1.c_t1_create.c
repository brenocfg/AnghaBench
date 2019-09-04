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
struct TYPE_3__ {scalar_t__ flagssize; scalar_t__ datasize; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * data; int /*<<< orphan*/  raw; int /*<<< orphan*/  mqc; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_create () ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  raw_create () ; 

opj_t1_t* t1_create(opj_common_ptr cinfo) {
	opj_t1_t *t1 = (opj_t1_t*) opj_malloc(sizeof(opj_t1_t));
	if(!t1)
		return NULL;

	t1->cinfo = cinfo;
	/* create MQC and RAW handles */
	t1->mqc = mqc_create();
	t1->raw = raw_create();

	t1->data=NULL;
	t1->flags=NULL;
	t1->datasize=0;
	t1->flagssize=0;

	return t1;
}