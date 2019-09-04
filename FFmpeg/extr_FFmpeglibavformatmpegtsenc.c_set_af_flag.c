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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static void set_af_flag(uint8_t *pkt, int flag)
{
    // expect at least one flag to set
    av_assert0(flag);

    if ((pkt[3] & 0x20) == 0) {
        // no AF yet, set adaptation field flag
        pkt[3] |= 0x20;
        // 1 byte length, no flags
        pkt[4] = 1;
        pkt[5] = 0;
    }
    pkt[5] |= flag;
}