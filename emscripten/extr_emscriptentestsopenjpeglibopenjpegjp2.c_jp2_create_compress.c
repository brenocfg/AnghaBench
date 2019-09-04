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
struct TYPE_4__ {int /*<<< orphan*/ * j2k; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;

/* Variables and functions */
 int /*<<< orphan*/ * j2k_create_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jp2_destroy_compress (TYPE_1__*) ; 
 scalar_t__ opj_malloc (int) ; 

opj_jp2_t* jp2_create_compress(opj_common_ptr cinfo) {
	opj_jp2_t *jp2 = (opj_jp2_t*)opj_malloc(sizeof(opj_jp2_t));
	if(jp2) {
		jp2->cinfo = cinfo;
		/* create the J2K codec */
		jp2->j2k = j2k_create_compress(cinfo);
		if(jp2->j2k == NULL) {
			jp2_destroy_compress(jp2);
			return NULL;
		}
	}
	return jp2;
}