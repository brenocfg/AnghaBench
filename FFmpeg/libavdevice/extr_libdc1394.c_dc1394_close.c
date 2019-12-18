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
struct dc1394_data {int /*<<< orphan*/  d; int /*<<< orphan*/  camera; } ;
struct TYPE_3__ {struct dc1394_data* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  DC1394_OFF ; 
 int /*<<< orphan*/  dc1394_camera_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_capture_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc1394_video_set_transmission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dc1394_close(AVFormatContext * context)
{
    struct dc1394_data *dc1394 = context->priv_data;

    dc1394_video_set_transmission(dc1394->camera, DC1394_OFF);
    dc1394_capture_stop(dc1394->camera);
    dc1394_camera_free(dc1394->camera);
    dc1394_free(dc1394->d);

    return 0;
}