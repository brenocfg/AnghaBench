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
struct subchannel_id {int dummy; } ;
struct schib {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/ * cio_reset_pgm_check_handler ; 
 scalar_t__ pgm_check_occured ; 
 int /*<<< orphan*/ * s390_base_pgm_handler_fn ; 
 int stsch_err (struct subchannel_id,struct schib*) ; 

__attribute__((used)) static int stsch_reset(struct subchannel_id schid, struct schib *addr)
{
	int rc;

	pgm_check_occured = 0;
	s390_base_pgm_handler_fn = cio_reset_pgm_check_handler;
	rc = stsch_err(schid, addr);
	s390_base_pgm_handler_fn = NULL;

	/* The program check handler could have changed pgm_check_occured. */
	barrier();

	if (pgm_check_occured)
		return -EIO;
	else
		return rc;
}