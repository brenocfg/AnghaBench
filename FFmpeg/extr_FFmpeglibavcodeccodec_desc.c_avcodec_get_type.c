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
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ AVCodecDescriptor ;

/* Variables and functions */
 int AVMEDIA_TYPE_UNKNOWN ; 
 TYPE_1__* avcodec_descriptor_get (int) ; 

enum AVMediaType avcodec_get_type(enum AVCodecID codec_id)
{
    const AVCodecDescriptor *desc = avcodec_descriptor_get(codec_id);
    return desc ? desc->type : AVMEDIA_TYPE_UNKNOWN;
}