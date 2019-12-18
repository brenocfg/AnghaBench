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
struct zfcp_fc_ns_handler_data {int /*<<< orphan*/  done; int /*<<< orphan*/  handler_data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_ns_handler(unsigned long data)
{
	struct zfcp_fc_ns_handler_data *compl_rec =
			(struct zfcp_fc_ns_handler_data *) data;

	if (compl_rec->handler)
		compl_rec->handler(compl_rec->handler_data);

	complete(&compl_rec->done);
}