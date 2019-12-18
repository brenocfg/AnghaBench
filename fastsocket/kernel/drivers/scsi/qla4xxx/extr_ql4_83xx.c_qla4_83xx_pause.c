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
struct scsi_qla_host {int dummy; } ;
struct qla4_83xx_reset_entry_hdr {scalar_t__ delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4_83xx_pause(struct scsi_qla_host *ha,
			    struct qla4_83xx_reset_entry_hdr *p_hdr)
{
	if (p_hdr->delay)
		mdelay((uint32_t)((long)p_hdr->delay));
}