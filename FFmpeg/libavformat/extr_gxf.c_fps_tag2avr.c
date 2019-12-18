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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int /*<<< orphan*/ * frame_rate_tab ; 

__attribute__((used)) static AVRational fps_tag2avr(int32_t fps) {
    if (fps < 1 || fps > 9) fps = 9;
    return frame_rate_tab[fps - 1];
}