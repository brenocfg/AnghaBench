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
struct TYPE_5__ {int /*<<< orphan*/  (* rdft_calc ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ RDFTContext ;
typedef  int /*<<< orphan*/  FFTSample ;

/* Variables and functions */
 int /*<<< orphan*/  av_rdft_calc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rdft_calc(RDFTContext *r, FFTSample *tab)
{
#if AVFFT
    av_rdft_calc(r, tab);
#else
    r->rdft_calc(r, tab);
#endif
}