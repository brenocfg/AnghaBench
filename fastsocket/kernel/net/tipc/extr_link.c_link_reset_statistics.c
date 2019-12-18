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
struct TYPE_2__ {int /*<<< orphan*/  recv_info; int /*<<< orphan*/  sent_info; } ;
struct link {int /*<<< orphan*/  next_in_no; TYPE_1__ stats; int /*<<< orphan*/  next_out_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void link_reset_statistics(struct link *l_ptr)
{
	memset(&l_ptr->stats, 0, sizeof(l_ptr->stats));
	l_ptr->stats.sent_info = l_ptr->next_out_no;
	l_ptr->stats.recv_info = l_ptr->next_in_no;
}