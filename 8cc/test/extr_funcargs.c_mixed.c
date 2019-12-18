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
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,float) ; 

__attribute__((used)) static void mixed(float v01, int v02, float v03, int v04, float v05, int v06, float v07, int v08,
           float v09, int v10, float v11, int v12, float v13, int v14, float v15, int v16,
           float v17, int v18, float v19, int v20, float v21, int v22, float v23, int v24,
           float v25, int v26, float v27, int v28, float v29, int v30, float v31, int v32,
           float v33, int v34, float v35, int v36, float v37, int v38, float v39, int v40) {
    expectf(1.0, v01);  expect(2, v02);  expectf(3.0, v03);  expect(4, v04);
    expectf(5.0, v05);  expect(6, v06);  expectf(7.0, v07);  expect(8, v08);
    expectf(9.0, v09);  expect(10, v10); expectf(11.0, v11); expect(12, v12);
    expectf(13.0, v13); expect(14, v14); expectf(15.0, v15); expect(16, v16);
    expectf(17.0, v17); expect(18, v18); expectf(19.0, v19); expect(20, v20);
    expectf(21.0, v21); expect(22, v22); expectf(23.0, v23); expect(24, v24);
    expectf(25.0, v25); expect(26, v26); expectf(27.0, v27); expect(28, v28);
    expectf(29.0, v29); expect(30, v30); expectf(31.0, v31); expect(32, v32);
    expectf(33.0, v33); expect(34, v34); expectf(35.0, v35); expect(36, v36);
    expectf(37.0, v37); expect(38, v38); expectf(39.0, v39); expect(40, v40);
}