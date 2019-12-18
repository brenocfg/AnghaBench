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
struct Exception {int /*<<< orphan*/  msg; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int print_to (struct Exception*,int,char*,struct Exception*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Exception_Show(var self, var out, int pos) {
  struct Exception* e = self;
  return print_to(out, pos, 
    "<'Exception' At 0x%p %$ - %$>", self, e->obj, e->msg);
}