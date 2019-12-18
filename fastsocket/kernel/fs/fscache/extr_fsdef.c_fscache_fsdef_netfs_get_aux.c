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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  unsigned int uint16_t ;
struct fscache_netfs {int /*<<< orphan*/  version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static uint16_t fscache_fsdef_netfs_get_aux(const void *cookie_netfs_data,
					    void *buffer, uint16_t bufmax)
{
	const struct fscache_netfs *netfs = cookie_netfs_data;
	unsigned dlen;

	_enter("{%s.%u},", netfs->name, netfs->version);

	dlen = sizeof(uint32_t);
	if (dlen > bufmax)
		return 0;

	memcpy(buffer, &netfs->version, dlen);
	return dlen;
}