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
struct pohmelfs_ctl {scalar_t__ idx; scalar_t__ type; scalar_t__ proto; scalar_t__ addrlen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline int pohmelfs_config_eql(struct pohmelfs_ctl *sc, struct pohmelfs_ctl *ctl)
{
	if (sc->idx == ctl->idx && sc->type == ctl->type &&
			sc->proto == ctl->proto &&
			sc->addrlen == ctl->addrlen &&
			!memcmp(&sc->addr, &ctl->addr, ctl->addrlen))
		return 1;

	return 0;
}