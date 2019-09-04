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
typedef  int /*<<< orphan*/  u_int32_t ;
struct kctl {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct kctl* ctl_find_by_name (char const*) ; 
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

u_int32_t
ctl_id_by_name(const char *name)
{
	u_int32_t	ctl_id = 0;
	struct kctl	*kctl;

	lck_mtx_lock(ctl_mtx);
	kctl = ctl_find_by_name(name);
	if (kctl)
		ctl_id = kctl->id;
	lck_mtx_unlock(ctl_mtx);

	return (ctl_id);
}