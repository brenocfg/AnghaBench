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
typedef  int /*<<< orphan*/  AM_MEDIA_TYPE ;

/* Variables and functions */

void ff_print_AM_MEDIA_TYPE(const AM_MEDIA_TYPE *type)
{
#if DSHOWDEBUG
    dshowdebug("    majortype\t");
    ff_printGUID(&type->majortype);
    dshowdebug("\n");
    dshowdebug("    subtype\t");
    ff_printGUID(&type->subtype);
    dshowdebug("\n");
    dshowdebug("    bFixedSizeSamples\t%d\n", type->bFixedSizeSamples);
    dshowdebug("    bTemporalCompression\t%d\n", type->bTemporalCompression);
    dshowdebug("    lSampleSize\t%lu\n", type->lSampleSize);
    dshowdebug("    formattype\t");
    ff_printGUID(&type->formattype);
    dshowdebug("\n");
    dshowdebug("    pUnk\t%p\n", type->pUnk);
    dshowdebug("    cbFormat\t%lu\n", type->cbFormat);
    dshowdebug("    pbFormat\t%p\n", type->pbFormat);

    if (IsEqualGUID(&type->formattype, &FORMAT_VideoInfo)) {
        VIDEOINFOHEADER *v = (void *) type->pbFormat;
        dshowdebug("      rcSource: left %ld top %ld right %ld bottom %ld\n",
                   v->rcSource.left, v->rcSource.top, v->rcSource.right, v->rcSource.bottom);
        dshowdebug("      rcTarget: left %ld top %ld right %ld bottom %ld\n",
                   v->rcTarget.left, v->rcTarget.top, v->rcTarget.right, v->rcTarget.bottom);
        dshowdebug("      dwBitRate: %lu\n", v->dwBitRate);
        dshowdebug("      dwBitErrorRate: %lu\n", v->dwBitErrorRate);
        dshowdebug("      AvgTimePerFrame: %"PRId64"\n", v->AvgTimePerFrame);
        dump_bih(NULL, &v->bmiHeader);
    } else if (IsEqualGUID(&type->formattype, &FORMAT_VideoInfo2)) {
        VIDEOINFOHEADER2 *v = (void *) type->pbFormat;
        dshowdebug("      rcSource: left %ld top %ld right %ld bottom %ld\n",
                   v->rcSource.left, v->rcSource.top, v->rcSource.right, v->rcSource.bottom);
        dshowdebug("      rcTarget: left %ld top %ld right %ld bottom %ld\n",
                   v->rcTarget.left, v->rcTarget.top, v->rcTarget.right, v->rcTarget.bottom);
        dshowdebug("      dwBitRate: %lu\n", v->dwBitRate);
        dshowdebug("      dwBitErrorRate: %lu\n", v->dwBitErrorRate);
        dshowdebug("      AvgTimePerFrame: %"PRId64"\n", v->AvgTimePerFrame);
        dshowdebug("      dwInterlaceFlags: %lu\n", v->dwInterlaceFlags);
        dshowdebug("      dwCopyProtectFlags: %lu\n", v->dwCopyProtectFlags);
        dshowdebug("      dwPictAspectRatioX: %lu\n", v->dwPictAspectRatioX);
        dshowdebug("      dwPictAspectRatioY: %lu\n", v->dwPictAspectRatioY);
//        dshowdebug("      dwReserved1: %lu\n", v->u.dwReserved1); /* mingw-w64 is buggy and doesn't name unnamed unions */
        dshowdebug("      dwReserved2: %lu\n", v->dwReserved2);
        dump_bih(NULL, &v->bmiHeader);
    } else if (IsEqualGUID(&type->formattype, &FORMAT_WaveFormatEx)) {
        WAVEFORMATEX *fx = (void *) type->pbFormat;
        dshowdebug("      wFormatTag: %u\n", fx->wFormatTag);
        dshowdebug("      nChannels: %u\n", fx->nChannels);
        dshowdebug("      nSamplesPerSec: %lu\n", fx->nSamplesPerSec);
        dshowdebug("      nAvgBytesPerSec: %lu\n", fx->nAvgBytesPerSec);
        dshowdebug("      nBlockAlign: %u\n", fx->nBlockAlign);
        dshowdebug("      wBitsPerSample: %u\n", fx->wBitsPerSample);
        dshowdebug("      cbSize: %u\n", fx->cbSize);
    }
#endif
}