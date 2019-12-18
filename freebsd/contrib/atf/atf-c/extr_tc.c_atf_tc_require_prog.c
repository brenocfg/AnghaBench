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
struct TYPE_3__ {int /*<<< orphan*/ * tc; } ;

/* Variables and functions */
 TYPE_1__ Current ; 
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _atf_tc_require_prog (TYPE_1__*,char const*) ; 

void
atf_tc_require_prog(const char *prog)
{
    PRE(Current.tc != NULL);

    _atf_tc_require_prog(&Current, prog);
}