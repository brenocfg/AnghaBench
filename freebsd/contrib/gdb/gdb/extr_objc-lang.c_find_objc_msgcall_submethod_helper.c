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
struct objc_submethod_helper_data {scalar_t__ (* f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  new_pc; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
find_objc_msgcall_submethod_helper (void * arg)
{
  struct objc_submethod_helper_data *s = 
    (struct objc_submethod_helper_data *) arg;

  if (s->f (s->pc, s->new_pc) == 0) 
    return 1;
  else 
    return 0;
}