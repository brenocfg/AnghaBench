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
typedef  struct Exception* var ;
struct Exception {int /*<<< orphan*/  buffers; int /*<<< orphan*/  active; int /*<<< orphan*/  depth; int /*<<< orphan*/  msg; int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int EXCEPTION_MAX_DEPTH ; 
 int /*<<< orphan*/  Exception ; 
 int /*<<< orphan*/  assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Exception* cast (struct Exception*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Exception_Assign(var self, var obj) {
  struct Exception* e = self;
  struct Exception* o = cast(obj, Exception);
  e->obj = o->obj;
  assign(e->msg, o->msg);
  e->depth = o->depth;
  e->active = o->active;
  memcpy(e->buffers, o->buffers, sizeof(jmp_buf*) * EXCEPTION_MAX_DEPTH);
}