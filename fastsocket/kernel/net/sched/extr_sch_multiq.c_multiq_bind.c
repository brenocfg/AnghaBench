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
typedef  int /*<<< orphan*/  u32 ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 unsigned long multiq_get (struct Qdisc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long multiq_bind(struct Qdisc *sch, unsigned long parent,
				 u32 classid)
{
	return multiq_get(sch, classid);
}