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
struct ub_scsi_cmd {struct completion* back; } ;
struct ub_dev {int dummy; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 

__attribute__((used)) static void ub_probe_done(struct ub_dev *sc, struct ub_scsi_cmd *cmd)
{
	struct completion *cop = cmd->back;
	complete(cop);
}