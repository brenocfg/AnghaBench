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
struct TYPE_4__ {int* data; int h; int w; int flags_stride; int /*<<< orphan*/ * flags; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  flag_t ;

/* Variables and functions */
 int /*<<< orphan*/  t1_dec_refpass_step_mqc (TYPE_1__*,int /*<<< orphan*/ *,int*,int,int) ; 

__attribute__((used)) static void t1_dec_refpass_mqc(
		opj_t1_t *t1,
		int bpno)
{
	int i, j, k, one, poshalf, neghalf;
	int *data1 = t1->data;
	flag_t *flags1 = &t1->flags[1];
	one = 1 << bpno;
	poshalf = one >> 1;
	neghalf = bpno > 0 ? -poshalf : -1;
	for (k = 0; k < (t1->h & ~3); k += 4) {
		for (i = 0; i < t1->w; ++i) {
			int *data2 = data1 + i;
			flag_t *flags2 = flags1 + i;
			flags2 += t1->flags_stride;
			t1_dec_refpass_step_mqc(t1, flags2, data2, poshalf, neghalf);
			data2 += t1->w;
			flags2 += t1->flags_stride;
			t1_dec_refpass_step_mqc(t1, flags2, data2, poshalf, neghalf);
			data2 += t1->w;
			flags2 += t1->flags_stride;
			t1_dec_refpass_step_mqc(t1, flags2, data2, poshalf, neghalf);
			data2 += t1->w;
			flags2 += t1->flags_stride;
			t1_dec_refpass_step_mqc(t1, flags2, data2, poshalf, neghalf);
			data2 += t1->w;
		}
		data1 += t1->w << 2;
		flags1 += t1->flags_stride << 2;
	}
	for (i = 0; i < t1->w; ++i) {
		int *data2 = data1 + i;
		flag_t *flags2 = flags1 + i;
		for (j = k; j < t1->h; ++j) {
			flags2 += t1->flags_stride;
			t1_dec_refpass_step_mqc(t1, flags2, data2, poshalf, neghalf);
			data2 += t1->w;
		}
	}
}