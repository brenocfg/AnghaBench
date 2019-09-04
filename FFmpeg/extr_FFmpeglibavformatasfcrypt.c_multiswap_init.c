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
typedef  int uint32_t ;

/* Variables and functions */
 int AV_RL32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void multiswap_init(const uint8_t keybuf[48], uint32_t keys[12])
{
    int i;
    for (i = 0; i < 12; i++)
        keys[i] = AV_RL32(keybuf + (i << 2)) | 1;
}