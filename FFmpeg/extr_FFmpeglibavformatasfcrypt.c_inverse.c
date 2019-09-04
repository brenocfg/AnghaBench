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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t inverse(uint32_t v)
{
    // v ^ 3 gives the inverse (mod 16), could also be implemented
    // as table etc. (only lowest 4 bits matter!)
    uint32_t inverse = v * v * v;
    // uses a fixpoint-iteration that doubles the number
    // of correct lowest bits each time
    inverse *= 2 - v * inverse;
    inverse *= 2 - v * inverse;
    inverse *= 2 - v * inverse;
    return inverse;
}