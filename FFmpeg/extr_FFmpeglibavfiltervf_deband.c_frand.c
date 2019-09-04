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
 float floorf (float const) ; 
 double sinf (int) ; 

__attribute__((used)) static float frand(int x, int y)
{
    const float r = sinf(x * 12.9898 + y * 78.233) * 43758.545;

    return r - floorf(r);
}