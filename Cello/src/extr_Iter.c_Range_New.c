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
typedef  struct Range* var ;
struct Range {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Int ; 
 int /*<<< orphan*/  new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_stack (struct Range*,struct Range*) ; 

__attribute__((used)) static void Range_New(var self, var args) {
  struct Range* r = self;
  r->value = new(Int);  
  range_stack(self, args);
}