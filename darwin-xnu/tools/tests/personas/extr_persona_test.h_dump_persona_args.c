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
struct kpersona_info {int dummy; } ;
struct persona_args {int flags; int /*<<< orphan*/  override_uid; struct kpersona_info kinfo; } ;

/* Variables and functions */
 int PA_HAS_UID ; 
 int /*<<< orphan*/  _dump_kpersona (int /*<<< orphan*/ *,int,struct kpersona_info const*) ; 
 int /*<<< orphan*/  info (char*,...) ; 

__attribute__((used)) static inline void dump_persona_args(const char *msg, const struct persona_args *pa)
{
	const struct kpersona_info *ki = &pa->kinfo;

	if (msg)
		info("%s", msg);
	info("\t flags: 0x%x", pa->flags);
	info("\t %cuid: %d", pa->flags & PA_HAS_UID ? '+' : '-', pa->override_uid);
	_dump_kpersona(NULL, pa->flags, ki);
}