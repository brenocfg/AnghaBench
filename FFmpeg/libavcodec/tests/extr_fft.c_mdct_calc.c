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
struct TYPE_5__ {int /*<<< orphan*/  (* mdct_calc ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_1__ FFTContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_mdct_calc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void mdct_calc(FFTContext *s, FFTSample *output, const FFTSample *input)
{
#if AVFFT
    av_mdct_calc(s, output, input);
#else
    s->mdct_calc(s, output, input);
#endif
}