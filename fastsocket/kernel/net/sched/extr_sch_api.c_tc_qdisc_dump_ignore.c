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
struct Qdisc {int flags; } ;

/* Variables and functions */
 int TCQ_F_BUILTIN ; 

__attribute__((used)) static bool tc_qdisc_dump_ignore(struct Qdisc *q)
{
	return (q->flags & TCQ_F_BUILTIN) ? true : false;
}