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
struct TYPE_3__ {scalar_t__ pic_order_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  picture_id; } ;
typedef  TYPE_1__ VAPictureHEVC ;

/* Variables and functions */
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  VA_PICTURE_HEVC_INVALID ; 

__attribute__((used)) static void init_vaapi_pic(VAPictureHEVC *va_pic)
{
    va_pic->picture_id    = VA_INVALID_ID;
    va_pic->flags         = VA_PICTURE_HEVC_INVALID;
    va_pic->pic_order_cnt = 0;
}