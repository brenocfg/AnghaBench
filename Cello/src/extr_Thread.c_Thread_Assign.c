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
typedef  struct Thread* var ;
struct Thread {scalar_t__ tls; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  Table ; 
 int /*<<< orphan*/  Thread ; 
 scalar_t__ alloc_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign (scalar_t__,scalar_t__) ; 
 struct Thread* cast (struct Thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Thread_Assign(var self, var obj) {
  struct Thread* t = self;
  struct Thread* o = cast(obj, Thread);
  t->func = o->func;
  t->tls = t->tls ? t->tls : alloc_raw(Table);
  assign(t->tls, o->tls);
}