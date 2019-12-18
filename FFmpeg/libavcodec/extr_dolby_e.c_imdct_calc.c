#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* imdct; } ;
struct TYPE_10__ {size_t imdct_idx; int imdct_phs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_1__*,float*,float*) ;int /*<<< orphan*/  (* imdct_calc ) (TYPE_1__*,float*,float*) ;} ;
typedef  TYPE_1__ FFTContext ;
typedef  TYPE_2__ DBEGroup ;
typedef  TYPE_3__ DBEContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int* imdct_bits_tab ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,float*,float*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,float*,float*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,float*,float*) ; 

__attribute__((used)) static void imdct_calc(DBEContext *s, DBEGroup *g, float *result, float *values)
{
    FFTContext *imdct = &s->imdct[g->imdct_idx];
    int n   = 1 << imdct_bits_tab[g->imdct_idx];
    int n2  = n >> 1;
    int i;

    switch (g->imdct_phs) {
    case 0:
        imdct->imdct_half(imdct, result, values);
        for (i = 0; i < n2; i++)
            result[n2 + i] = result[n2 - i - 1];
        break;
    case 1:
        imdct->imdct_calc(imdct, result, values);
        break;
    case 2:
        imdct->imdct_half(imdct, result + n2, values);
        for (i = 0; i < n2; i++)
            result[i] = -result[n - i - 1];
        break;
    default:
        av_assert0(0);
    }
}