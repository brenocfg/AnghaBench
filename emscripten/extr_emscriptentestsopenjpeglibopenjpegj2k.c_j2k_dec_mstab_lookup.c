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
struct TYPE_4__ {int id; } ;
typedef  TYPE_1__ opj_dec_mstabent_t ;

/* Variables and functions */
 TYPE_1__* j2k_dec_mstab ; 

__attribute__((used)) static opj_dec_mstabent_t *j2k_dec_mstab_lookup(int id) {
	opj_dec_mstabent_t *e;
	for (e = j2k_dec_mstab; e->id != 0; e++) {
		if (e->id == id) {
			break;
		}
	}
	return e;
}