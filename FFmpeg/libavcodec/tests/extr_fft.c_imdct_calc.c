#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct FFTContext {int /*<<< orphan*/  (* imdct_calc ) (struct FFTContext*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
typedef  int /*<<< orphan*/  FFTSample ;

/* Variables and functions */
 int /*<<< orphan*/  av_imdct_calc (struct FFTContext*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (struct FFTContext*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void imdct_calc(struct FFTContext *s, FFTSample *output, const FFTSample *input)
{
#if AVFFT
    av_imdct_calc(s, output, input);
#else
    s->imdct_calc(s, output, input);
#endif
}