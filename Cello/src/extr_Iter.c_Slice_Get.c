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
 int /*<<< orphan*/  Range_Get (int /*<<< orphan*/ ,struct Slice*) ; 
 struct Slice* get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static var Slice_Get(var self, var key) {
  struct Slice* s = self;
  return get(s->iter, Range_Get(s->range, key));
}