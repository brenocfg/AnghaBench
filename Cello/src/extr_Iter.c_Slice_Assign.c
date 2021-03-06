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
typedef  struct Slice* var ;
struct Slice {int /*<<< orphan*/  range; int /*<<< orphan*/  iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  Slice ; 
 int /*<<< orphan*/  assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Slice* cast (struct Slice*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Slice_Assign(var self, var obj) {
  struct Slice* s = self;
  struct Slice* o = cast(obj, Slice);
  s->iter = o->iter;
  assign(s->range, o->range);
}