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
typedef  enum AVPictureType { ____Placeholder_AVPictureType } AVPictureType ;

/* Variables and functions */
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_NONE ; 
 int AV_PICTURE_TYPE_P ; 
 int AV_PICTURE_TYPE_SI ; 
 int AV_PICTURE_TYPE_SP ; 
#define  MFX_FRAMETYPE_B 131 
#define  MFX_FRAMETYPE_I 130 
#define  MFX_FRAMETYPE_P 129 
 int MFX_FRAMETYPE_S ; 
#define  MFX_FRAMETYPE_UNKNOWN 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

enum AVPictureType ff_qsv_map_pictype(int mfx_pic_type)
{
    enum AVPictureType type;
    switch (mfx_pic_type & 0x7) {
    case MFX_FRAMETYPE_I:
        if (mfx_pic_type & MFX_FRAMETYPE_S)
            type = AV_PICTURE_TYPE_SI;
        else
            type = AV_PICTURE_TYPE_I;
        break;
    case MFX_FRAMETYPE_B:
        type = AV_PICTURE_TYPE_B;
        break;
    case MFX_FRAMETYPE_P:
        if (mfx_pic_type & MFX_FRAMETYPE_S)
            type = AV_PICTURE_TYPE_SP;
        else
            type = AV_PICTURE_TYPE_P;
        break;
    case MFX_FRAMETYPE_UNKNOWN:
        type = AV_PICTURE_TYPE_NONE;
        break;
    default:
        av_assert0(0);
    }

    return type;
}