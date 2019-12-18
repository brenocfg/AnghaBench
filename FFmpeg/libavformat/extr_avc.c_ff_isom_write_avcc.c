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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB24 (int const*) ; 
 int AV_RB32 (int const*) ; 
 int FFMIN (int,int) ; 
 int H264_MAX_PPS_COUNT ; 
 int H264_MAX_SPS_COUNT ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  av_free (int*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int**) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int const*,int) ; 
 int ff_avc_parse_nal_units_buf (int const*,int**,int*) ; 

int ff_isom_write_avcc(AVIOContext *pb, const uint8_t *data, int len)
{
    AVIOContext *sps_pb = NULL, *pps_pb = NULL;
    uint8_t *buf = NULL, *end, *start = NULL;
    uint8_t *sps = NULL, *pps = NULL;
    uint32_t sps_size = 0, pps_size = 0;
    int ret, nb_sps = 0, nb_pps = 0;

    if (len <= 6)
        return AVERROR_INVALIDDATA;

    /* check for H.264 start code */
    if (AV_RB32(data) != 0x00000001 &&
        AV_RB24(data) != 0x000001) {
        avio_write(pb, data, len);
        return 0;
    }

    ret = ff_avc_parse_nal_units_buf(data, &buf, &len);
    if (ret < 0)
        return ret;
    start = buf;
    end = buf + len;

    ret = avio_open_dyn_buf(&sps_pb);
    if (ret < 0)
        goto fail;
    ret = avio_open_dyn_buf(&pps_pb);
    if (ret < 0)
        goto fail;

    /* look for sps and pps */
    while (end - buf > 4) {
        uint32_t size;
        uint8_t nal_type;
        size = FFMIN(AV_RB32(buf), end - buf - 4);
        buf += 4;
        nal_type = buf[0] & 0x1f;

        if (nal_type == 7) { /* SPS */
            nb_sps++;
            if (size > UINT16_MAX || nb_sps >= H264_MAX_SPS_COUNT) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            avio_wb16(sps_pb, size);
            avio_write(sps_pb, buf, size);
        } else if (nal_type == 8) { /* PPS */
            nb_pps++;
            if (size > UINT16_MAX || nb_pps >= H264_MAX_PPS_COUNT) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            avio_wb16(pps_pb, size);
            avio_write(pps_pb, buf, size);
        }

        buf += size;
    }
    sps_size = avio_close_dyn_buf(sps_pb, &sps);
    pps_size = avio_close_dyn_buf(pps_pb, &pps);

    if (sps_size < 6 || !pps_size) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    avio_w8(pb, 1); /* version */
    avio_w8(pb, sps[3]); /* profile */
    avio_w8(pb, sps[4]); /* profile compat */
    avio_w8(pb, sps[5]); /* level */
    avio_w8(pb, 0xff); /* 6 bits reserved (111111) + 2 bits nal size length - 1 (11) */
    avio_w8(pb, 0xe0 | nb_sps); /* 3 bits reserved (111) + 5 bits number of sps */

    avio_write(pb, sps, sps_size);
    avio_w8(pb, nb_pps); /* number of pps */
    avio_write(pb, pps, pps_size);

fail:
    if (!sps)
        avio_close_dyn_buf(sps_pb, &sps);
    if (!pps)
        avio_close_dyn_buf(pps_pb, &pps);
    av_free(sps);
    av_free(pps);
    av_free(start);

    return ret;
}