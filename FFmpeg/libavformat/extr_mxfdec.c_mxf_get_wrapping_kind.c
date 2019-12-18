#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int* UID ;
struct TYPE_3__ {size_t wrapping_indicator_pos; int wrapping_indicator_type; int /*<<< orphan*/ * uid; } ;
typedef  int /*<<< orphan*/  MXFWrappingScheme ;
typedef  TYPE_1__ MXFCodecUL ;

/* Variables and functions */
 int /*<<< orphan*/  ClipWrapped ; 
#define  D10D11Wrap 130 
 int /*<<< orphan*/  FrameWrapped ; 
#define  RawAWrap 129 
#define  RawVWrap 128 
 int /*<<< orphan*/  UnknownWrapped ; 
 int /*<<< orphan*/  mxf_data_essence_container_uls ; 
 TYPE_1__* mxf_get_codec_ul (int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  mxf_picture_essence_container_uls ; 
 int /*<<< orphan*/  mxf_sound_essence_container_uls ; 

__attribute__((used)) static MXFWrappingScheme mxf_get_wrapping_kind(UID *essence_container_ul)
{
    int val;
    const MXFCodecUL *codec_ul;

    codec_ul = mxf_get_codec_ul(mxf_picture_essence_container_uls, essence_container_ul);
    if (!codec_ul->uid[0])
        codec_ul = mxf_get_codec_ul(mxf_sound_essence_container_uls, essence_container_ul);
    if (!codec_ul->uid[0])
        codec_ul = mxf_get_codec_ul(mxf_data_essence_container_uls, essence_container_ul);
    if (!codec_ul->uid[0] || !codec_ul->wrapping_indicator_pos)
        return UnknownWrapped;

    val = (*essence_container_ul)[codec_ul->wrapping_indicator_pos];
    switch (codec_ul->wrapping_indicator_type) {
        case RawVWrap:
            val = val % 4;
            break;
        case RawAWrap:
            if (val == 0x03 || val == 0x04)
                val -= 0x02;
            break;
        case D10D11Wrap:
            if (val == 0x02)
                val = 0x01;
            break;
    }
    if (val == 0x01)
        return FrameWrapped;
    if (val == 0x02)
        return ClipWrapped;
    return UnknownWrapped;
}