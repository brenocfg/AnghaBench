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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  NV12 ; 
 int /*<<< orphan*/  NV21 ; 
 int /*<<< orphan*/  SET_FF_NVX_TO_ALL_RGBX_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SWS_ACCURATE_RND ; 
 int /*<<< orphan*/  YUV420P ; 
 int /*<<< orphan*/  YUV422P ; 
 int /*<<< orphan*/  nv12 ; 
 int /*<<< orphan*/  nv21 ; 
 int /*<<< orphan*/  yuv420p ; 
 int /*<<< orphan*/  yuv422p ; 

__attribute__((used)) static void get_unscaled_swscale_neon(SwsContext *c) {
    int accurate_rnd = c->flags & SWS_ACCURATE_RND;

    SET_FF_NVX_TO_ALL_RGBX_FUNC(nv12, NV12, accurate_rnd);
    SET_FF_NVX_TO_ALL_RGBX_FUNC(nv21, NV21, accurate_rnd);
    SET_FF_NVX_TO_ALL_RGBX_FUNC(yuv420p, YUV420P, accurate_rnd);
    SET_FF_NVX_TO_ALL_RGBX_FUNC(yuv422p, YUV422P, accurate_rnd);
}