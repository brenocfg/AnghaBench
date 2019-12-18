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
struct irb {int dummy; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 

__attribute__((used)) static void
dasd_diag_dump_sense(struct dasd_device *device, struct dasd_ccw_req * req,
		     struct irb *stat)
{
	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "dump sense not available for DIAG data");
}