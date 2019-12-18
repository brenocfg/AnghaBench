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
struct ata_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_check_ready ; 
 int ata_wait_ready (struct ata_link*,unsigned long,int /*<<< orphan*/ ) ; 

int ata_sff_wait_ready(struct ata_link *link, unsigned long deadline)
{
	return ata_wait_ready(link, deadline, ata_sff_check_ready);
}