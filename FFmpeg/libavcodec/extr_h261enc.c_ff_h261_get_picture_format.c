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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 

int ff_h261_get_picture_format(int width, int height)
{
    // QCIF
    if (width == 176 && height == 144)
        return 0;
    // CIF
    else if (width == 352 && height == 288)
        return 1;
    // ERROR
    else
        return AVERROR(EINVAL);
}