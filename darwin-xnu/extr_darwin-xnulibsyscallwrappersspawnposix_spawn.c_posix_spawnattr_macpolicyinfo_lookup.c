#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  policyname; } ;
typedef  TYPE_1__ _ps_mac_policy_extension_t ;
typedef  TYPE_2__* _posix_spawn_mac_policy_extensions_t ;
struct TYPE_6__ {int psmx_count; TYPE_1__* psmx_extensions; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static
_ps_mac_policy_extension_t *
posix_spawnattr_macpolicyinfo_lookup(_posix_spawn_mac_policy_extensions_t psmx, const char *policyname)
{
	int i;

	if (psmx == NULL)
		return NULL;
	
	for (i = 0; i < psmx->psmx_count; i++) {
		_ps_mac_policy_extension_t *extension = &psmx->psmx_extensions[i];
		if (strcmp(extension->policyname, policyname) == 0)
			return extension;
	}
	return NULL;
}