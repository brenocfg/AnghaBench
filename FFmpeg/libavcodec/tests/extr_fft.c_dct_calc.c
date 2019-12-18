#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* dct_calc ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_1__ DCTContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dct_calc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dct_calc(DCTContext *d, FFTSample *data)
{
#if AVFFT
    av_dct_calc(d, data);
#else
    d->dct_calc(d, data);
#endif
}