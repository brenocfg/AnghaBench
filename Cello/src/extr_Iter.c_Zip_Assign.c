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
typedef  struct Zip* var ;
struct Zip {int /*<<< orphan*/  values; int /*<<< orphan*/  iters; } ;

/* Variables and functions */
 int /*<<< orphan*/  Zip ; 
 int /*<<< orphan*/  assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Zip* cast (struct Zip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Zip_Assign(var self, var obj) {
  struct Zip* z = self;
  struct Zip* o = cast(obj, Zip);
  assign(z->iters, o->iters);
  assign(z->values, o->values);
}