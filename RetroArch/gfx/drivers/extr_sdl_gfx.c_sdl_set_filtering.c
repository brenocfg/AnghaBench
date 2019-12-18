#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  scaler_type; } ;
struct TYPE_4__ {TYPE_1__ scaler; } ;
typedef  TYPE_2__ sdl_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_TYPE_BILINEAR ; 
 int /*<<< orphan*/  SCALER_TYPE_POINT ; 

__attribute__((used)) static void sdl_set_filtering(void *data, unsigned index, bool smooth)
{
   sdl_video_t *vid = (sdl_video_t*)data;
   vid->scaler.scaler_type = smooth ? SCALER_TYPE_BILINEAR : SCALER_TYPE_POINT;
}