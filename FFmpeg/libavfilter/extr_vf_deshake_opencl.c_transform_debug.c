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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 double M_PI ; 
 size_t RingbufRot ; 
 size_t RingbufScaleX ; 
 size_t RingbufScaleY ; 
 size_t RingbufX ; 
 size_t RingbufY ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float) ; 

__attribute__((used)) static void transform_debug(AVFilterContext *avctx, float *new_vals, float *old_vals, int curr_frame) {
    av_log(avctx, AV_LOG_VERBOSE,
        "Frame %d:\n"
        "\tframe moved from: %f x, %f y\n"
        "\t              to: %f x, %f y\n"
        "\t    rotated from: %f degrees\n"
        "\t              to: %f degrees\n"
        "\t     scaled from: %f x, %f y\n"
        "\t              to: %f x, %f y\n"
        "\n"
        "\tframe moved by: %f x, %f y\n"
        "\t    rotated by: %f degrees\n"
        "\t     scaled by: %f x, %f y\n",
        curr_frame,
        old_vals[RingbufX], old_vals[RingbufY],
        new_vals[RingbufX], new_vals[RingbufY],
        old_vals[RingbufRot] * (180.0 / M_PI),
        new_vals[RingbufRot] * (180.0 / M_PI),
        old_vals[RingbufScaleX], old_vals[RingbufScaleY],
        new_vals[RingbufScaleX], new_vals[RingbufScaleY],
        old_vals[RingbufX] - new_vals[RingbufX], old_vals[RingbufY] - new_vals[RingbufY],
        old_vals[RingbufRot] * (180.0 / M_PI) - new_vals[RingbufRot] * (180.0 / M_PI),
        new_vals[RingbufScaleX] / old_vals[RingbufScaleX], new_vals[RingbufScaleY] / old_vals[RingbufScaleY]
    );
}