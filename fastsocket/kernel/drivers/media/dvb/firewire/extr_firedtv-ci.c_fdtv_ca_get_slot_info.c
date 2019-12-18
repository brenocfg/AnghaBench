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
struct firedtv_tuner_status {int dummy; } ;
struct firedtv {int dummy; } ;
struct ca_slot_info {scalar_t__ num; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_CI ; 
 int EFAULT ; 
 scalar_t__ avc_tuner_status (struct firedtv*,struct firedtv_tuner_status*) ; 
 int /*<<< orphan*/  fdtv_get_ca_flags (struct firedtv_tuner_status*) ; 

__attribute__((used)) static int fdtv_ca_get_slot_info(struct firedtv *fdtv, void *arg)
{
	struct firedtv_tuner_status stat;
	struct ca_slot_info *slot = arg;

	if (avc_tuner_status(fdtv, &stat))
		return -EFAULT;

	if (slot->num != 0)
		return -EFAULT;

	slot->type = CA_CI;
	slot->flags = fdtv_get_ca_flags(&stat);
	return 0;
}