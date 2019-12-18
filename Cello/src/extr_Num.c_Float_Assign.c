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
typedef  struct Float* var ;
struct Float {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_float (struct Float*) ; 

__attribute__((used)) static void Float_Assign(var self, var obj) {
  struct Float* f = self;
  f->val = c_float(obj);
}