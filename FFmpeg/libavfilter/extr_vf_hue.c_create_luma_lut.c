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
struct TYPE_3__ {float brightness; int /*<<< orphan*/ * lut_l16; int /*<<< orphan*/ * lut_l; } ;
typedef  TYPE_1__ HueContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int) ; 
 int /*<<< orphan*/  av_clip_uintp2 (int,int) ; 

__attribute__((used)) static inline void create_luma_lut(HueContext *h)
{
    const float b = h->brightness;
    int i;

    for (i = 0; i < 256; i++) {
        h->lut_l[i] = av_clip_uint8(i + b * 25.5);
    }
    for (i = 0; i < 65536; i++) {
        h->lut_l16[i] = av_clip_uintp2(i + b * 102.4, 10);
    }
}