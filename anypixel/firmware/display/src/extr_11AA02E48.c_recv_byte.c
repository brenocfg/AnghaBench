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
 int rwbit (int,int) ; 

__attribute__((used)) static bool recv_byte(uint8_t *byte, bool mak) {
    uint8_t i, work;
    for(i = 0; i < 8; i++)
        work = (work << 1) | rwbit(true, true);
    *byte = work;
    rwbit(!mak, mak);
    return rwbit(true, true); // return the SAK
}