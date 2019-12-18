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
 int /*<<< orphan*/  expectf (int,float) ; 

__attribute__((used)) static void many_floats(float v01, float v02, float v03, float v04, float v05,
                 float v06, float v07, float v08, float v09, float v10,
                 float v11, float v12, float v13, float v14, float v15,
                 float v16, float v17) {
    expectf(1, v01);  expectf(2, v02);  expectf(3, v03);  expectf(4, v04);
    expectf(5, v05);  expectf(6, v06);  expectf(7, v07);  expectf(8, v08);
    expectf(9, v09);  expectf(10, v10); expectf(11, v11); expectf(12, v12);
    expectf(13, v13); expectf(14, v14); expectf(15, v15); expectf(16, v16);
    expectf(17, v17);
}