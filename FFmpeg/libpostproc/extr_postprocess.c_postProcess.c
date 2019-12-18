#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  pp_mode ;
typedef  int /*<<< orphan*/  (* pp_fn ) (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ;
typedef  int /*<<< orphan*/  pp_context ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_11__ {int lumMode; } ;
struct TYPE_10__ {int cpuCaps; TYPE_2__ ppMode; } ;
typedef  TYPE_2__ PPMode ;
typedef  TYPE_1__ PPContext ;

/* Variables and functions */
 int AV_CPU_FLAG_3DNOW ; 
 int AV_CPU_FLAG_ALTIVEC ; 
 int AV_CPU_FLAG_MMX ; 
 int AV_CPU_FLAG_MMXEXT ; 
 int AV_CPU_FLAG_SSE2 ; 
 int BITEXACT ; 
 int /*<<< orphan*/  postProcess_3DNow (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  postProcess_C (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  postProcess_MMX (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  postProcess_MMX2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  postProcess_SSE2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  postProcess_altivec (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*,int,int,TYPE_1__*) ; 

__attribute__((used)) static inline void postProcess(const uint8_t src[], int srcStride, uint8_t dst[], int dstStride, int width, int height,
        const int8_t QPs[], int QPStride, int isColor, pp_mode *vm, pp_context *vc)
{
    pp_fn pp = postProcess_C;
    PPContext *c= (PPContext *)vc;
    PPMode *ppMode= (PPMode *)vm;
    c->ppMode= *ppMode; //FIXME

    if (!(ppMode->lumMode & BITEXACT)) {
#if CONFIG_RUNTIME_CPUDETECT
#if ARCH_X86 && HAVE_INLINE_ASM
        // ordered per speed fastest first
        if      (c->cpuCaps & AV_CPU_FLAG_SSE2)     pp = postProcess_SSE2;
        else if (c->cpuCaps & AV_CPU_FLAG_MMXEXT)   pp = postProcess_MMX2;
        else if (c->cpuCaps & AV_CPU_FLAG_3DNOW)    pp = postProcess_3DNow;
        else if (c->cpuCaps & AV_CPU_FLAG_MMX)      pp = postProcess_MMX;
#elif HAVE_ALTIVEC
        if      (c->cpuCaps & AV_CPU_FLAG_ALTIVEC)  pp = postProcess_altivec;
#endif
#else /* CONFIG_RUNTIME_CPUDETECT */
#if     HAVE_SSE2_INLINE
        pp = postProcess_SSE2;
#elif   HAVE_MMXEXT_INLINE
        pp = postProcess_MMX2;
#elif HAVE_AMD3DNOW_INLINE
        pp = postProcess_3DNow;
#elif HAVE_MMX_INLINE
        pp = postProcess_MMX;
#elif HAVE_ALTIVEC
        pp = postProcess_altivec;
#endif
#endif /* !CONFIG_RUNTIME_CPUDETECT */
    }

    pp(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
}