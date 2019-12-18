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
struct TYPE_3__ {int present; void* max_pic_average_light_level; void* max_content_light_level; } ;
typedef  TYPE_1__ HEVCSEIContentLight ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_nal_sei_content_light_info(HEVCSEIContentLight *s, GetBitContext *gb)
{
    // Max and average light levels
    s->max_content_light_level     = get_bits_long(gb, 16);
    s->max_pic_average_light_level = get_bits_long(gb, 16);
    // As this SEI message comes before the first frame that references it,
    // initialize the flag to 2 and decrement on IRAP access unit so it
    // persists for the coded video sequence (e.g., between two IRAPs)
    s->present = 2;
    return  0;
}