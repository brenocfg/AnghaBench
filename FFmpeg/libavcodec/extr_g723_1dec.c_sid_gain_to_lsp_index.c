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

__attribute__((used)) static int sid_gain_to_lsp_index(int gain)
{
    if (gain < 0x10)
        return gain << 6;
    else if (gain < 0x20)
        return gain - 8 << 7;
    else
        return gain - 20 << 8;
}