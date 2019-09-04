#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cstr_info; int /*<<< orphan*/  cio; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ opj_j2k_t ;
struct TYPE_4__ {scalar_t__ main_head_start; scalar_t__ codestream_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  J2K_STATE_MHSIZ ; 
 scalar_t__ cio_numbytesleft (int /*<<< orphan*/ ) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j2k_read_soc(opj_j2k_t *j2k) {	
	j2k->state = J2K_STATE_MHSIZ;
	/* Index */
	if (j2k->cstr_info) {
		j2k->cstr_info->main_head_start = cio_tell(j2k->cio) - 2;
		j2k->cstr_info->codestream_size = cio_numbytesleft(j2k->cio) + 2 - j2k->cstr_info->main_head_start;
	}
}