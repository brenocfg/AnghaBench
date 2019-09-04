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
 int /*<<< orphan*/  lerp13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lerp13rgb(uint8_t *out, uint8_t *p1, uint8_t *p2)
{
    out[0] = lerp13(p1[0], p2[0]);
    out[1] = lerp13(p1[1], p2[1]);
    out[2] = lerp13(p1[2], p2[2]);
}