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

/* Variables and functions */
 unsigned int AV_RB16 (int /*<<< orphan*/  const*) ; 
 unsigned int AV_RL16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned int read16(const uint8_t **ptr, int is_big)
{
    unsigned int temp;
    if (is_big) {
        temp = AV_RB16(*ptr);
    } else {
        temp = AV_RL16(*ptr);
    }
    *ptr += 2;
    return temp;
}