#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uLongf ;
struct TYPE_16__ {int /*<<< orphan*/  seekable; } ;
struct TYPE_15__ {int size; scalar_t__ type; } ;
struct TYPE_14__ {int /*<<< orphan*/  fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  int /*<<< orphan*/  Bytef ;
typedef  TYPE_3__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_malloc (long) ; 
 long avio_rb32 (TYPE_3__*) ; 
 scalar_t__ avio_rl32 (TYPE_3__*) ; 
 scalar_t__ ffio_init_context (TYPE_3__*,int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ffio_read_size (TYPE_3__*,int /*<<< orphan*/ *,long) ; 
 int mov_read_default (TYPE_1__*,TYPE_3__*,TYPE_2__) ; 
 scalar_t__ uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,long) ; 

__attribute__((used)) static int mov_read_cmov(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
#if CONFIG_ZLIB
    AVIOContext ctx;
    uint8_t *cmov_data;
    uint8_t *moov_data; /* uncompressed data */
    long cmov_len, moov_len;
    int ret = -1;

    avio_rb32(pb); /* dcom atom */
    if (avio_rl32(pb) != MKTAG('d','c','o','m'))
        return AVERROR_INVALIDDATA;
    if (avio_rl32(pb) != MKTAG('z','l','i','b')) {
        av_log(c->fc, AV_LOG_ERROR, "unknown compression for cmov atom !\n");
        return AVERROR_INVALIDDATA;
    }
    avio_rb32(pb); /* cmvd atom */
    if (avio_rl32(pb) != MKTAG('c','m','v','d'))
        return AVERROR_INVALIDDATA;
    moov_len = avio_rb32(pb); /* uncompressed size */
    cmov_len = atom.size - 6 * 4;

    cmov_data = av_malloc(cmov_len);
    if (!cmov_data)
        return AVERROR(ENOMEM);
    moov_data = av_malloc(moov_len);
    if (!moov_data) {
        av_free(cmov_data);
        return AVERROR(ENOMEM);
    }
    ret = ffio_read_size(pb, cmov_data, cmov_len);
    if (ret < 0)
        goto free_and_return;

    ret = AVERROR_INVALIDDATA;
    if (uncompress (moov_data, (uLongf *) &moov_len, (const Bytef *)cmov_data, cmov_len) != Z_OK)
        goto free_and_return;
    if (ffio_init_context(&ctx, moov_data, moov_len, 0, NULL, NULL, NULL, NULL) != 0)
        goto free_and_return;
    ctx.seekable = AVIO_SEEKABLE_NORMAL;
    atom.type = MKTAG('m','o','o','v');
    atom.size = moov_len;
    ret = mov_read_default(c, &ctx, atom);
free_and_return:
    av_free(moov_data);
    av_free(cmov_data);
    return ret;
#else
    av_log(c->fc, AV_LOG_ERROR, "this file requires zlib support compiled in\n");
    return AVERROR(ENOSYS);
#endif
}