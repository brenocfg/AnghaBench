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
struct TYPE_4__ {int h; int w; int flags_stride; int /*<<< orphan*/ * data; int /*<<< orphan*/ * flags; } ;
typedef  TYPE_1__ opj_t1_t ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_VSC ; 
 int /*<<< orphan*/  t1_dec_refpass_step_raw (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void t1_dec_refpass_raw(
		opj_t1_t *t1,
		int bpno,
		int cblksty)
{
	int i, j, k, one, poshalf, neghalf;
	int vsc;
	one = 1 << bpno;
	poshalf = one >> 1;
	neghalf = bpno > 0 ? -poshalf : -1;
	for (k = 0; k < t1->h; k += 4) {
		for (i = 0; i < t1->w; ++i) {
			for (j = k; j < k + 4 && j < t1->h; ++j) {
				vsc = ((cblksty & J2K_CCP_CBLKSTY_VSC) && (j == k + 3 || j == t1->h - 1)) ? 1 : 0;
				t1_dec_refpass_step_raw(
						t1,
						&t1->flags[((j+1) * t1->flags_stride) + i + 1],
						&t1->data[(j * t1->w) + i],
						poshalf,
						neghalf,
						vsc);
			}
		}
	}
}