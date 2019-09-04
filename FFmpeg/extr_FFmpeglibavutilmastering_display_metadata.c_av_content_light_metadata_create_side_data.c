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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVContentLightMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  AV_FRAME_DATA_CONTENT_LIGHT_LEVEL ; 
 TYPE_1__* av_frame_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        sizeof(AVContentLightMetadata));
    if (!side_data)
        return NULL;

    memset(side_data->data, 0, sizeof(AVContentLightMetadata));

    return (AVContentLightMetadata *)side_data->data;
}