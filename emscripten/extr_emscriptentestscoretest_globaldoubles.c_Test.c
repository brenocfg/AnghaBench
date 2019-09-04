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
 int /*<<< orphan*/  printf (char*,...) ; 
 double testVu ; 
 double testVv ; 
 double testWu ; 
 double testWv ; 

void Test(double _testVu, double _testVv, double _testWu, double _testWv) {
  testVu = _testVu;
  testVv = _testVv;
  testWu = _testWu;
  testWv = _testWv;
  printf("BUG?\n");
  printf("Display: Vu=%f  Vv=%f  Wu=%f  Wv=%f\n", testVu, testVv, testWu,
         testWv);
}