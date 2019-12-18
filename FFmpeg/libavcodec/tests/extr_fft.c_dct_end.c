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
typedef  int /*<<< orphan*/  DCTContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dct_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dct_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dct_end(DCTContext *d)
{
#if AVFFT
    av_dct_end(d);
#else
    ff_dct_end(d);
#endif
}