#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
struct TYPE_4__ {scalar_t__ datalen; scalar_t__ data; } ;
typedef  TYPE_1__ _ps_mac_policy_extension_t ;
typedef  TYPE_2__* _posix_spawnattr_t ;
struct TYPE_5__ {int /*<<< orphan*/  psa_mac_extensions; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 TYPE_1__* posix_spawnattr_macpolicyinfo_lookup (int /*<<< orphan*/ ,char const*) ; 

int
posix_spawnattr_getmacpolicyinfo_np(const posix_spawnattr_t * __restrict attr,
		const char *policyname, void **datap, size_t *datalenp)
{
	_posix_spawnattr_t psattr;
	_ps_mac_policy_extension_t *extension;

	if (attr == NULL || *attr == NULL || policyname == NULL || datap == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	extension = posix_spawnattr_macpolicyinfo_lookup(psattr->psa_mac_extensions, policyname);
	if (extension == NULL)
		return ESRCH;
	*datap = (void *)(uintptr_t)extension->data;
	if (datalenp != NULL) {
		*datalenp = (size_t)extension->datalen;
	}
	return 0;
}