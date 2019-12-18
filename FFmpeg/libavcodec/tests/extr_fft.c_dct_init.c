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
typedef  enum DCTTransformType { ____Placeholder_DCTTransformType } DCTTransformType ;
typedef  int /*<<< orphan*/  DCTContext ;

/* Variables and functions */
 int /*<<< orphan*/ * av_dct_init (int,int) ; 
 int /*<<< orphan*/  ff_dct_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void dct_init(DCTContext **d, int nbits, enum DCTTransformType trans)
{
#if AVFFT
    *d = av_dct_init(nbits, trans);
#else
    ff_dct_init(*d, nbits, trans);
#endif
}