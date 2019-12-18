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
typedef  struct Function* var ;
struct Function {struct Function* (* func ) (struct Function*) ;} ;

/* Variables and functions */
 struct Function* stub1 (struct Function*) ; 

__attribute__((used)) static var Function_Call(var self, var args) {
  struct Function* f = self;
  return f->func(args);
}