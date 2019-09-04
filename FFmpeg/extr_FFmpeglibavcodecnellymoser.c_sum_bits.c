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
 int /*<<< orphan*/  NELLY_BIT_CAP ; 
 int NELLY_FILL_LEN ; 
 scalar_t__ av_clip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sum_bits(short *buf, short shift, short off)
{
    int i, ret = 0;

    for (i = 0; i < NELLY_FILL_LEN; i++) {
        int b = buf[i]-off;
        b = ((b>>(shift-1))+1)>>1;
        ret += av_clip(b, 0, NELLY_BIT_CAP);
    }

    return ret;
}