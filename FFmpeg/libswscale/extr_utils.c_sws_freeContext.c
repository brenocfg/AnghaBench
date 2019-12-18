#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  inv_gamma; int /*<<< orphan*/  gamma; int /*<<< orphan*/ * cascaded1_tmp; int /*<<< orphan*/ * cascaded_tmp; struct TYPE_8__** cascaded_context; int /*<<< orphan*/  formatConvBuffer; int /*<<< orphan*/  yuvTable; struct TYPE_8__* chrMmxextFilterCode; struct TYPE_8__* lumMmxextFilterCode; int /*<<< orphan*/  chrMmxextFilterCodeSize; int /*<<< orphan*/  lumMmxextFilterCodeSize; int /*<<< orphan*/  hChrFilterPos; int /*<<< orphan*/  hLumFilterPos; int /*<<< orphan*/  vChrFilterPos; int /*<<< orphan*/  vLumFilterPos; int /*<<< orphan*/  vCCoeffsBank; int /*<<< orphan*/  vYCoeffsBank; int /*<<< orphan*/  hChrFilter; int /*<<< orphan*/  hLumFilter; int /*<<< orphan*/  vChrFilter; int /*<<< orphan*/  vLumFilter; int /*<<< orphan*/ * dither_error; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  VirtualFree (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_free_filters (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sws_freeContext(SwsContext *c)
{
    int i;
    if (!c)
        return;

    for (i = 0; i < 4; i++)
        av_freep(&c->dither_error[i]);

    av_freep(&c->vLumFilter);
    av_freep(&c->vChrFilter);
    av_freep(&c->hLumFilter);
    av_freep(&c->hChrFilter);
#if HAVE_ALTIVEC
    av_freep(&c->vYCoeffsBank);
    av_freep(&c->vCCoeffsBank);
#endif

    av_freep(&c->vLumFilterPos);
    av_freep(&c->vChrFilterPos);
    av_freep(&c->hLumFilterPos);
    av_freep(&c->hChrFilterPos);

#if HAVE_MMX_INLINE
#if USE_MMAP
    if (c->lumMmxextFilterCode)
        munmap(c->lumMmxextFilterCode, c->lumMmxextFilterCodeSize);
    if (c->chrMmxextFilterCode)
        munmap(c->chrMmxextFilterCode, c->chrMmxextFilterCodeSize);
#elif HAVE_VIRTUALALLOC
    if (c->lumMmxextFilterCode)
        VirtualFree(c->lumMmxextFilterCode, 0, MEM_RELEASE);
    if (c->chrMmxextFilterCode)
        VirtualFree(c->chrMmxextFilterCode, 0, MEM_RELEASE);
#else
    av_free(c->lumMmxextFilterCode);
    av_free(c->chrMmxextFilterCode);
#endif
    c->lumMmxextFilterCode = NULL;
    c->chrMmxextFilterCode = NULL;
#endif /* HAVE_MMX_INLINE */

    av_freep(&c->yuvTable);
    av_freep(&c->formatConvBuffer);

    sws_freeContext(c->cascaded_context[0]);
    sws_freeContext(c->cascaded_context[1]);
    sws_freeContext(c->cascaded_context[2]);
    memset(c->cascaded_context, 0, sizeof(c->cascaded_context));
    av_freep(&c->cascaded_tmp[0]);
    av_freep(&c->cascaded1_tmp[0]);

    av_freep(&c->gamma);
    av_freep(&c->inv_gamma);

    ff_free_filters(c);

    av_free(c);
}