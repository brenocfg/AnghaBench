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
struct Zip {struct Tuple* values; int /*<<< orphan*/  iters; } ;
struct Tuple {int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  Terminal ; 
 int /*<<< orphan*/  _ ; 
 size_t len (int /*<<< orphan*/ ) ; 

var zip_stack(var self) {
  struct Zip* z = self;
  size_t nargs = len(z->iters);
  struct Tuple* t = z->values;
  for (size_t i = 0; i < nargs; i++) {
    t->items[i] = _;
  }
  t->items[nargs] = Terminal;
  return z;
}