#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  essence_codec_ul; int /*<<< orphan*/  essence_container_ul; } ;
typedef  TYPE_1__ MXFDescriptor ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 TYPE_3__* mxf_get_codec_ul (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxf_intra_only_essence_container_uls ; 
 int /*<<< orphan*/  mxf_intra_only_picture_essence_coding_uls ; 

__attribute__((used)) static int mxf_is_intra_only(MXFDescriptor *descriptor)
{
    return mxf_get_codec_ul(mxf_intra_only_essence_container_uls,
                            &descriptor->essence_container_ul)->id != AV_CODEC_ID_NONE ||
           mxf_get_codec_ul(mxf_intra_only_picture_essence_coding_uls,
                            &descriptor->essence_codec_ul)->id     != AV_CODEC_ID_NONE;
}