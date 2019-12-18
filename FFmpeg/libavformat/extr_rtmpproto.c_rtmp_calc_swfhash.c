#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float uint8_t ;
typedef  int int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {int swfsize; int /*<<< orphan*/  swfverify; } ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AVSEEK_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 float* av_malloc (int) ; 
 int /*<<< orphan*/  av_opt_set_bin (TYPE_2__*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int ff_rtmp_calc_digest (float*,int,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  ffurl_close (TYPE_1__*) ; 
 int ffurl_open_whitelist (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ffurl_read_complete (TYPE_1__*,float*,int) ; 
 int ffurl_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (float*,char*,int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int rtmp_uncompress_swfplayer (float*,int,float**,int*) ; 

__attribute__((used)) static int rtmp_calc_swfhash(URLContext *s)
{
    RTMPContext *rt = s->priv_data;
    uint8_t *in_data = NULL, *out_data = NULL, *swfdata;
    int64_t in_size;
    URLContext *stream;
    char swfhash[32];
    int swfsize;
    int ret = 0;

    /* Get the SWF player file. */
    if ((ret = ffurl_open_whitelist(&stream, rt->swfverify, AVIO_FLAG_READ,
                                    &s->interrupt_callback, NULL,
                                    s->protocol_whitelist, s->protocol_blacklist, s)) < 0) {
        av_log(s, AV_LOG_ERROR, "Cannot open connection %s.\n", rt->swfverify);
        goto fail;
    }

    if ((in_size = ffurl_seek(stream, 0, AVSEEK_SIZE)) < 0) {
        ret = AVERROR(EIO);
        goto fail;
    }

    if (!(in_data = av_malloc(in_size))) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if ((ret = ffurl_read_complete(stream, in_data, in_size)) < 0)
        goto fail;

    if (in_size < 3) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (!memcmp(in_data, "CWS", 3)) {
#if CONFIG_ZLIB
        int64_t out_size;
        /* Decompress the SWF player file using Zlib. */
        if (!(out_data = av_malloc(8))) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        *in_data = 'F'; // magic stuff
        memcpy(out_data, in_data, 8);
        out_size = 8;

        if ((ret = rtmp_uncompress_swfplayer(in_data + 8, in_size - 8,
                                             &out_data, &out_size)) < 0)
            goto fail;
        swfsize = out_size;
        swfdata = out_data;
#else
        av_log(s, AV_LOG_ERROR,
               "Zlib is required for decompressing the SWF player file.\n");
        ret = AVERROR(EINVAL);
        goto fail;
#endif
    } else {
        swfsize = in_size;
        swfdata = in_data;
    }

    /* Compute the SHA256 hash of the SWF player file. */
    if ((ret = ff_rtmp_calc_digest(swfdata, swfsize, 0,
                                   "Genuine Adobe Flash Player 001", 30,
                                   swfhash)) < 0)
        goto fail;

    /* Set SWFVerification parameters. */
    av_opt_set_bin(rt, "rtmp_swfhash", swfhash, 32, 0);
    rt->swfsize = swfsize;

fail:
    av_freep(&in_data);
    av_freep(&out_data);
    ffurl_close(stream);
    return ret;
}