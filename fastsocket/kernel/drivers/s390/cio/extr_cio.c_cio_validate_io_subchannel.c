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
struct subchannel {int /*<<< orphan*/  schib; } ;

/* Variables and functions */
 int ENODEV ; 
 int cio_check_devno_blacklisted (struct subchannel*) ; 
 int /*<<< orphan*/  css_sch_is_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cio_validate_io_subchannel(struct subchannel *sch)
{
	/* Initialization for io subchannels. */
	if (!css_sch_is_valid(&sch->schib))
		return -ENODEV;

	/* Devno is valid. */
	return cio_check_devno_blacklisted(sch);
}