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
typedef  struct Tuple* var ;
struct Tuple {struct Tuple** items; } ;

/* Variables and functions */
 int Tuple_Len (struct Tuple*) ; 

__attribute__((used)) static var Tuple_Iter_Last(var self) {
  struct Tuple* t = self;
  return t->items[Tuple_Len(t)-1];
}