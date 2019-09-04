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
typedef  int /*<<< orphan*/  FlashSV2Context ;

/* Variables and functions */

__attribute__((used)) static int write_palette(FlashSV2Context * s, uint8_t * buf, int buf_size)
{
    //this isn't implemented yet!  Default palette only!
    return -1;
}