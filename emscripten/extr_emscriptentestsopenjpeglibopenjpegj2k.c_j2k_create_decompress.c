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
typedef  int /*<<< orphan*/  opj_tcp_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tile_data; int /*<<< orphan*/  cinfo; int /*<<< orphan*/ * default_tcp; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;

/* Variables and functions */
 scalar_t__ opj_calloc (int,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

opj_j2k_t* j2k_create_decompress(opj_common_ptr cinfo) {
	opj_j2k_t *j2k = (opj_j2k_t*) opj_calloc(1, sizeof(opj_j2k_t));
	if(!j2k)
		return NULL;

	j2k->default_tcp = (opj_tcp_t*) opj_calloc(1, sizeof(opj_tcp_t));
	if(!j2k->default_tcp) {
		opj_free(j2k);
		return NULL;
	}

	j2k->cinfo = cinfo;
	j2k->tile_data = NULL;

	return j2k;
}