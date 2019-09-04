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
 int T1_NMSEDEC_FRACBITS ; 
 int /*<<< orphan*/  t1_enc_sigpass_step (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int*,char,int) ; 

__attribute__((used)) static void t1_enc_sigpass(
		opj_t1_t *t1,
		int bpno,
		int orient,
		int *nmsedec,
		char type,
		int cblksty)
{
	int i, j, k, one, vsc;
	*nmsedec = 0;
	one = 1 << (bpno + T1_NMSEDEC_FRACBITS);
	for (k = 0; k < t1->h; k += 4) {
		for (i = 0; i < t1->w; ++i) {
			for (j = k; j < k + 4 && j < t1->h; ++j) {
				vsc = ((cblksty & J2K_CCP_CBLKSTY_VSC) && (j == k + 3 || j == t1->h - 1)) ? 1 : 0;
				t1_enc_sigpass_step(
						t1,
						&t1->flags[((j+1) * t1->flags_stride) + i + 1],
						&t1->data[(j * t1->w) + i],
						orient,
						bpno,
						one,
						nmsedec,
						type,
						vsc);
			}
		}
	}
}