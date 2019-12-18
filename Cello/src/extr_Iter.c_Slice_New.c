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
struct Slice {int /*<<< orphan*/  range; } ;

/* Variables and functions */
 int /*<<< orphan*/  Range ; 
 int /*<<< orphan*/  new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slice_stack (struct Slice*,struct Slice*) ; 

__attribute__((used)) static void Slice_New(var self, var args) {
  struct Slice* s = self;
  s->range = new(Range);
  slice_stack(self, args);
}