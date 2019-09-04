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

/* Variables and functions */
 int round (double) ; 

__attribute__((used)) static inline int frame_size(int sample_rate, int frame_len_msec)
{
    const int frame_size = round((double)sample_rate * (frame_len_msec / 1000.0));
    return frame_size + (frame_size % 2);
}