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
typedef  enum AVFieldOrder { ____Placeholder_AVFieldOrder } AVFieldOrder ;

/* Variables and functions */
 int AV_FIELD_BB ; 
 int AV_FIELD_PROGRESSIVE ; 
 int AV_FIELD_TT ; 
 int AV_FIELD_UNKNOWN ; 
#define  MFX_PICSTRUCT_FIELD_BFF 130 
#define  MFX_PICSTRUCT_FIELD_TFF 129 
#define  MFX_PICSTRUCT_PROGRESSIVE 128 

enum AVFieldOrder ff_qsv_map_picstruct(int mfx_pic_struct)
{
    enum AVFieldOrder field = AV_FIELD_UNKNOWN;
    switch (mfx_pic_struct & 0xF) {
    case MFX_PICSTRUCT_PROGRESSIVE:
        field = AV_FIELD_PROGRESSIVE;
        break;
    case MFX_PICSTRUCT_FIELD_TFF:
        field = AV_FIELD_TT;
        break;
    case MFX_PICSTRUCT_FIELD_BFF:
        field = AV_FIELD_BB;
        break;
    }

    return field;
}