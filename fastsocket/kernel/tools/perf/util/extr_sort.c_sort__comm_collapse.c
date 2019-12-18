#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {TYPE_1__* thread; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {char* comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_null (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int64_t
sort__comm_collapse(struct hist_entry *left, struct hist_entry *right)
{
	char *comm_l = left->thread->comm;
	char *comm_r = right->thread->comm;

	if (!comm_l || !comm_r)
		return cmp_null(comm_l, comm_r);

	return strcmp(comm_l, comm_r);
}