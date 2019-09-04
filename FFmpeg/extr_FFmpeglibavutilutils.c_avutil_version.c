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

/* Variables and functions */
 int AVMEDIA_TYPE_ATTACHMENT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int AV_PICTURE_TYPE_BI ; 
 int AV_SAMPLE_FMT_DBLP ; 
 scalar_t__ HAVE_MMX2 ; 
 scalar_t__ HAVE_MMXEXT ; 
 int LIBAVUTIL_VERSION_INT ; 
 int LIBAVUTIL_VERSION_MICRO ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int av_sat_dadd32 (int,int) ; 
 long long llrint (long long) ; 

unsigned avutil_version(void)
{
    static int checks_done;
    if (checks_done)
        return LIBAVUTIL_VERSION_INT;

    av_assert0(AV_SAMPLE_FMT_DBLP == 9);
    av_assert0(AVMEDIA_TYPE_ATTACHMENT == 4);
    av_assert0(AV_PICTURE_TYPE_BI == 7);
    av_assert0(LIBAVUTIL_VERSION_MICRO >= 100);
    av_assert0(HAVE_MMX2 == HAVE_MMXEXT);

    av_assert0(((size_t)-1) > 0); // C guarantees this but if false on a platform we care about revert at least b284e1ffe343d6697fb950d1ee517bafda8a9844

    if (av_sat_dadd32(1, 2) != 5) {
        av_log(NULL, AV_LOG_FATAL, "Libavutil has been built with a broken binutils, please upgrade binutils and rebuild\n");
        abort();
    }

    if (llrint(1LL<<60) != 1LL<<60) {
        av_log(NULL, AV_LOG_ERROR, "Libavutil has been linked to a broken llrint()\n");
    }

    checks_done = 1;
    return LIBAVUTIL_VERSION_INT;
}