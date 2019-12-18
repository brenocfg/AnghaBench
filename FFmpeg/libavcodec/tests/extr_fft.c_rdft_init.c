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
typedef  enum RDFTransformType { ____Placeholder_RDFTransformType } RDFTransformType ;
typedef  int /*<<< orphan*/  RDFTContext ;

/* Variables and functions */
 int /*<<< orphan*/ * av_rdft_init (int,int) ; 
 int /*<<< orphan*/  ff_rdft_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void rdft_init(RDFTContext **r, int nbits, enum RDFTransformType trans)
{
#if AVFFT
    *r = av_rdft_init(nbits, trans);
#else
    ff_rdft_init(*r, nbits, trans);
#endif
}