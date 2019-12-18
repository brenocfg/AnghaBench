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
struct libipw_device {TYPE_1__** networks; } ;
struct TYPE_2__ {struct TYPE_2__* ibss_dfs; } ;

/* Variables and functions */
 int MAX_NETWORK_COUNT ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static inline void libipw_networks_free(struct libipw_device *ieee)
{
	int i;

	for (i = 0; i < MAX_NETWORK_COUNT; i++) {
		if (ieee->networks[i]->ibss_dfs)
			kfree(ieee->networks[i]->ibss_dfs);
		kfree(ieee->networks[i]);
	}
}