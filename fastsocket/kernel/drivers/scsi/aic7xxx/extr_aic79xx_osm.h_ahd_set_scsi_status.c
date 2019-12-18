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
typedef  int /*<<< orphan*/  uint32_t ;
struct scb {int /*<<< orphan*/  io_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_cmd_set_scsi_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void ahd_set_scsi_status(struct scb *scb, uint32_t status)
{
	ahd_cmd_set_scsi_status(scb->io_ctx, status);
}