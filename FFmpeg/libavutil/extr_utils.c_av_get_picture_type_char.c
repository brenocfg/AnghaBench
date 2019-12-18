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
#define  AV_PICTURE_TYPE_B 134 
#define  AV_PICTURE_TYPE_BI 133 
#define  AV_PICTURE_TYPE_I 132 
#define  AV_PICTURE_TYPE_P 131 
#define  AV_PICTURE_TYPE_S 130 
#define  AV_PICTURE_TYPE_SI 129 
#define  AV_PICTURE_TYPE_SP 128 

char av_get_picture_type_char(enum AVPictureType pict_type)
{
    switch (pict_type) {
    case AV_PICTURE_TYPE_I:  return 'I';
    case AV_PICTURE_TYPE_P:  return 'P';
    case AV_PICTURE_TYPE_B:  return 'B';
    case AV_PICTURE_TYPE_S:  return 'S';
    case AV_PICTURE_TYPE_SI: return 'i';
    case AV_PICTURE_TYPE_SP: return 'p';
    case AV_PICTURE_TYPE_BI: return 'b';
    default:                 return '?';
    }
}