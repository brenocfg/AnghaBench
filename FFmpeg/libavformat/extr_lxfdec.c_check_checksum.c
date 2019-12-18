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
 scalar_t__ AV_RL32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int check_checksum(const uint8_t *header, int size)
{
    int x;
    uint32_t sum = 0;

    for (x = 0; x < size; x += 4)
        sum += AV_RL32(&header[x]);

    return sum;
}