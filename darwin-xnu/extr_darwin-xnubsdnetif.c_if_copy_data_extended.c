#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  ifi_fbytes; int /*<<< orphan*/  ifi_fpackets; int /*<<< orphan*/  ifi_dt_bytes; int /*<<< orphan*/  ifi_alignerrs; } ;
struct ifnet {TYPE_1__ if_data; } ;
struct if_data_extended {int /*<<< orphan*/  ifi_fbytes; int /*<<< orphan*/  ifi_fpackets; int /*<<< orphan*/  ifi_dt_bytes; int /*<<< orphan*/  ifi_alignerrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct if_data_extended*,int) ; 

void
if_copy_data_extended(struct ifnet *ifp, struct if_data_extended *if_de)
{
#define	COPY_IF_DE_FIELD64_ATOMIC(fld) do {			\
	atomic_get_64(if_de->fld,				\
	    (u_int64_t *)(void *)(uintptr_t)&ifp->if_data.fld);	\
} while (0)

	bzero(if_de, sizeof (*if_de));
	COPY_IF_DE_FIELD64_ATOMIC(ifi_alignerrs);
	COPY_IF_DE_FIELD64_ATOMIC(ifi_dt_bytes);
	COPY_IF_DE_FIELD64_ATOMIC(ifi_fpackets);
	COPY_IF_DE_FIELD64_ATOMIC(ifi_fbytes);

#undef COPY_IF_DE_FIELD64_ATOMIC
}