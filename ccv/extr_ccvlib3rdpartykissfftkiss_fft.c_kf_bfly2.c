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
typedef  int /*<<< orphan*/  kiss_fft_cpx ;
typedef  TYPE_1__* kiss_fft_cfg ;
struct TYPE_3__ {int /*<<< orphan*/ * twiddles; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ADDTO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_FIXDIV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  C_MUL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_SUB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kf_bfly2(
        kiss_fft_cpx * Fout,
        const size_t fstride,
        const kiss_fft_cfg st,
        int m
        )
{
    kiss_fft_cpx * Fout2;
    kiss_fft_cpx * tw1 = st->twiddles;
    kiss_fft_cpx t;
    Fout2 = Fout + m;
    do{
        C_FIXDIV(*Fout,2); C_FIXDIV(*Fout2,2);

        C_MUL (t,  *Fout2 , *tw1);
        tw1 += fstride;
        C_SUB( *Fout2 ,  *Fout , t );
        C_ADDTO( *Fout ,  t );
        ++Fout2;
        ++Fout;
    }while (--m);
}