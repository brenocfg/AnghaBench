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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  HEVCDecoderConfigurationRecord ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB24 (int const*) ; 
 int AV_RB32 (int const*) ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
#define  HEVC_NAL_PPS 132 
#define  HEVC_NAL_SEI_PREFIX 131 
#define  HEVC_NAL_SEI_SUFFIX 130 
#define  HEVC_NAL_SPS 129 
#define  HEVC_NAL_VPS 128 
 int /*<<< orphan*/  av_free (int*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int const*,int) ; 
 int ff_avc_parse_nal_units_buf (int const*,int**,int*) ; 
 int hvcc_add_nal_unit (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvcc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvcc_init (int /*<<< orphan*/ *) ; 
 int hvcc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ff_isom_write_hvcc(AVIOContext *pb, const uint8_t *data,
                       int size, int ps_array_completeness)
{
    int ret = 0;
    uint8_t *buf, *end, *start = NULL;
    HEVCDecoderConfigurationRecord hvcc;

    hvcc_init(&hvcc);

    if (size < 6) {
        /* We can't write a valid hvcC from the provided data */
        ret = AVERROR_INVALIDDATA;
        goto end;
    } else if (*data == 1) {
        /* Data is already hvcC-formatted */
        avio_write(pb, data, size);
        goto end;
    } else if (!(AV_RB24(data) == 1 || AV_RB32(data) == 1)) {
        /* Not a valid Annex B start code prefix */
        ret = AVERROR_INVALIDDATA;
        goto end;
    }

    ret = ff_avc_parse_nal_units_buf(data, &start, &size);
    if (ret < 0)
        goto end;

    buf = start;
    end = start + size;

    while (end - buf > 4) {
        uint32_t len = FFMIN(AV_RB32(buf), end - buf - 4);
        uint8_t type = (buf[4] >> 1) & 0x3f;

        buf += 4;

        switch (type) {
        case HEVC_NAL_VPS:
        case HEVC_NAL_SPS:
        case HEVC_NAL_PPS:
        case HEVC_NAL_SEI_PREFIX:
        case HEVC_NAL_SEI_SUFFIX:
            ret = hvcc_add_nal_unit(buf, len, ps_array_completeness, &hvcc);
            if (ret < 0)
                goto end;
            break;
        default:
            break;
        }

        buf += len;
    }

    ret = hvcc_write(pb, &hvcc);

end:
    hvcc_close(&hvcc);
    av_free(start);
    return ret;
}