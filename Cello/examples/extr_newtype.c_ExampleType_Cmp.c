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
typedef  struct ExampleType* var ;
struct ExampleType {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExampleType ; 
 struct ExampleType* cast (struct ExampleType*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ExampleType_Cmp(var self, var obj) {
  struct ExampleType* lhs = self;
  struct ExampleType* rhs = cast(obj, ExampleType);
  return lhs->value - rhs->value;
}