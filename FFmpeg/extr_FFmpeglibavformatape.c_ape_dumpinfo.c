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
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  APEContext ;

/* Variables and functions */

__attribute__((used)) static void ape_dumpinfo(AVFormatContext * s, APEContext * ape_ctx)
{
#ifdef DEBUG
    int i;

    av_log(s, AV_LOG_DEBUG, "Descriptor Block:\n\n");
    av_log(s, AV_LOG_DEBUG, "fileversion          = %"PRId16"\n", ape_ctx->fileversion);
    av_log(s, AV_LOG_DEBUG, "descriptorlength     = %"PRIu32"\n", ape_ctx->descriptorlength);
    av_log(s, AV_LOG_DEBUG, "headerlength         = %"PRIu32"\n", ape_ctx->headerlength);
    av_log(s, AV_LOG_DEBUG, "seektablelength      = %"PRIu32"\n", ape_ctx->seektablelength);
    av_log(s, AV_LOG_DEBUG, "wavheaderlength      = %"PRIu32"\n", ape_ctx->wavheaderlength);
    av_log(s, AV_LOG_DEBUG, "audiodatalength      = %"PRIu32"\n", ape_ctx->audiodatalength);
    av_log(s, AV_LOG_DEBUG, "audiodatalength_high = %"PRIu32"\n", ape_ctx->audiodatalength_high);
    av_log(s, AV_LOG_DEBUG, "wavtaillength        = %"PRIu32"\n", ape_ctx->wavtaillength);
    av_log(s, AV_LOG_DEBUG, "md5                  = ");
    for (i = 0; i < 16; i++)
         av_log(s, AV_LOG_DEBUG, "%02x", ape_ctx->md5[i]);
    av_log(s, AV_LOG_DEBUG, "\n");

    av_log(s, AV_LOG_DEBUG, "\nHeader Block:\n\n");

    av_log(s, AV_LOG_DEBUG, "compressiontype      = %"PRIu16"\n", ape_ctx->compressiontype);
    av_log(s, AV_LOG_DEBUG, "formatflags          = %"PRIu16"\n", ape_ctx->formatflags);
    av_log(s, AV_LOG_DEBUG, "blocksperframe       = %"PRIu32"\n", ape_ctx->blocksperframe);
    av_log(s, AV_LOG_DEBUG, "finalframeblocks     = %"PRIu32"\n", ape_ctx->finalframeblocks);
    av_log(s, AV_LOG_DEBUG, "totalframes          = %"PRIu32"\n", ape_ctx->totalframes);
    av_log(s, AV_LOG_DEBUG, "bps                  = %"PRIu16"\n", ape_ctx->bps);
    av_log(s, AV_LOG_DEBUG, "channels             = %"PRIu16"\n", ape_ctx->channels);
    av_log(s, AV_LOG_DEBUG, "samplerate           = %"PRIu32"\n", ape_ctx->samplerate);

    av_log(s, AV_LOG_DEBUG, "\nSeektable\n\n");
    if ((ape_ctx->seektablelength / sizeof(uint32_t)) != ape_ctx->totalframes) {
        av_log(s, AV_LOG_DEBUG, "No seektable\n");
    } else {
        for (i = 0; i < ape_ctx->seektablelength / sizeof(uint32_t); i++) {
            if (i < ape_ctx->totalframes - 1) {
                av_log(s, AV_LOG_DEBUG, "%8d   %"PRIu32" (%"PRIu32" bytes)",
                       i, ape_ctx->seektable[i],
                       ape_ctx->seektable[i + 1] - ape_ctx->seektable[i]);
                if (ape_ctx->bittable)
                    av_log(s, AV_LOG_DEBUG, " + %2d bits\n",
                           ape_ctx->bittable[i]);
                av_log(s, AV_LOG_DEBUG, "\n");
            } else {
                av_log(s, AV_LOG_DEBUG, "%8d   %"PRIu32"\n", i, ape_ctx->seektable[i]);
            }
        }
    }

    av_log(s, AV_LOG_DEBUG, "\nFrames\n\n");
    for (i = 0; i < ape_ctx->totalframes; i++)
        av_log(s, AV_LOG_DEBUG, "%8d   %8"PRId64" %8d (%d samples)\n", i,
               ape_ctx->frames[i].pos, ape_ctx->frames[i].size,
               ape_ctx->frames[i].nblocks);

    av_log(s, AV_LOG_DEBUG, "\nCalculated information:\n\n");
    av_log(s, AV_LOG_DEBUG, "junklength           = %"PRIu32"\n", ape_ctx->junklength);
    av_log(s, AV_LOG_DEBUG, "firstframe           = %"PRIu32"\n", ape_ctx->firstframe);
    av_log(s, AV_LOG_DEBUG, "totalsamples         = %"PRIu32"\n", ape_ctx->totalsamples);
#endif
}