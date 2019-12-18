#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** opt; char* val; } ;
typedef  TYPE_1__ opt_apply ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 void* expand_op (char*,int) ; 

__attribute__((used)) static void
expand_opts(opt_apply *p, int sel_p)
{
  if (*p->opt) {
    *p->opt = expand_op(*p->opt, sel_p);
  } else if (p->val) {
    /*
     * Do double expansion, remembering
     * to free the string from the first
     * expansion...
     */
    char *s = expand_op(p->val, TRUE);
    *p->opt = expand_op(s, sel_p);
    XFREE(s);
  }
}