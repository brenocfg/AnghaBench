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
typedef  int /*<<< orphan*/  HEVCSEI ;
typedef  int /*<<< orphan*/  HEVCParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int HEVC_NAL_SEI_PREFIX ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int decode_nal_sei_prefix (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int decode_nal_sei_suffix (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_nal_sei_message(GetBitContext *gb, void *logctx, HEVCSEI *s,
                                  const HEVCParamSets *ps, int nal_unit_type)
{
    int payload_type = 0;
    int payload_size = 0;
    int byte = 0xFF;
    av_log(logctx, AV_LOG_DEBUG, "Decoding SEI\n");

    while (byte == 0xFF) {
        if (get_bits_left(gb) < 16 || payload_type > INT_MAX - 255)
            return AVERROR_INVALIDDATA;
        byte          = get_bits(gb, 8);
        payload_type += byte;
    }
    byte = 0xFF;
    while (byte == 0xFF) {
        if (get_bits_left(gb) < 8 + 8LL*payload_size)
            return AVERROR_INVALIDDATA;
        byte          = get_bits(gb, 8);
        payload_size += byte;
    }
    if (nal_unit_type == HEVC_NAL_SEI_PREFIX) {
        return decode_nal_sei_prefix(gb, logctx, s, ps, payload_type, payload_size);
    } else { /* nal_unit_type == NAL_SEI_SUFFIX */
        return decode_nal_sei_suffix(gb, logctx, s, payload_type, payload_size);
    }
}