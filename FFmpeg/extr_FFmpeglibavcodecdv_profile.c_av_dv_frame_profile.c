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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVDVProfile ;

/* Variables and functions */
 int /*<<< orphan*/  const* ff_dv_frame_profile (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

const AVDVProfile *av_dv_frame_profile(const AVDVProfile *sys,
                                       const uint8_t *frame, unsigned buf_size)
{
    return ff_dv_frame_profile(NULL, sys, frame, buf_size);
}