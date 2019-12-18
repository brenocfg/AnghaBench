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
struct Zip {void* values; void* iters; } ;

/* Variables and functions */
 int /*<<< orphan*/  Tuple ; 
 int /*<<< orphan*/  _ ; 
 int /*<<< orphan*/  assign (void*,struct Zip*) ; 
 size_t len (struct Zip*) ; 
 void* new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Zip_New(var self, var args) {
  struct Zip* z = self;
  z->iters = new(Tuple);
  z->values = new(Tuple);
  assign(z->iters, args);
  for (size_t i = 0; i < len(args); i++) {
    push(z->values, _);
  }
}