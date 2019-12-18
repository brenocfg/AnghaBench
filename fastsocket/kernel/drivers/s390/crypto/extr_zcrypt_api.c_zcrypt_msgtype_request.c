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
struct zcrypt_ops {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct zcrypt_ops* __ops_lookup (unsigned char*,int) ; 
 int /*<<< orphan*/  request_module (unsigned char*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct zcrypt_ops *zcrypt_msgtype_request(unsigned char *name, int variant)
{
	struct zcrypt_ops *zops = NULL;

	zops = __ops_lookup(name, variant);
#ifndef CONFIG_ZCRYPT_MONOLITHIC
	if (!zops) {
		request_module(name);
		zops = __ops_lookup(name, variant);
	}
#endif
	if ((!zops) ||  (!try_module_get(zops->owner)))
		return NULL;
	return zops;
}