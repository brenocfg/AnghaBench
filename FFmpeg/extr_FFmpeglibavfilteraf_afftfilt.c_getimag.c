#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nb_exprs; int window_size; TYPE_1__** fft_data; } ;
struct TYPE_3__ {double im; } ;
typedef  TYPE_2__ AFFTFiltContext ;

/* Variables and functions */
 int av_clip (double,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline double getimag(void *priv, double x, double ch)
{
    AFFTFiltContext *s = priv;
    int ich, ix;

    ich = av_clip(ch, 0, s->nb_exprs - 1);
    ix = av_clip(x, 0, s->window_size / 2);

    return s->fft_data[ich][ix].im;
}