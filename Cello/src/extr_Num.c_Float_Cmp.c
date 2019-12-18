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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 double Float_C_Float (int /*<<< orphan*/ ) ; 
 double c_float (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Float_Cmp(var self, var obj) {
  double c = Float_C_Float(self) - c_float(obj);
  return c > 0 ? 1 : c < 0 ? -1 : 0;
}