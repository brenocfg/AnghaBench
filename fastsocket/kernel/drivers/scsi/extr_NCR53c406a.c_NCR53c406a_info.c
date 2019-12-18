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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 char const* info_msg ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static const char *NCR53c406a_info(struct Scsi_Host *SChost)
{
	DEB(printk("NCR53c406a_info called\n"));
	return (info_msg);
}