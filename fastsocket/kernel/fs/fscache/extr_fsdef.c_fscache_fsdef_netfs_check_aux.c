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
typedef  int /*<<< orphan*/  version ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct fscache_netfs {int /*<<< orphan*/  version; int /*<<< orphan*/  name; } ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;

/* Variables and functions */
 int FSCACHE_CHECKAUX_OBSOLETE ; 
 int FSCACHE_CHECKAUX_OKAY ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static enum fscache_checkaux fscache_fsdef_netfs_check_aux(
	void *cookie_netfs_data,
	const void *data,
	uint16_t datalen)
{
	struct fscache_netfs *netfs = cookie_netfs_data;
	uint32_t version;

	_enter("{%s},,%hu", netfs->name, datalen);

	if (datalen != sizeof(version)) {
		_leave(" = OBSOLETE [dl=%d v=%zu]", datalen, sizeof(version));
		return FSCACHE_CHECKAUX_OBSOLETE;
	}

	memcpy(&version, data, sizeof(version));
	if (version != netfs->version) {
		_leave(" = OBSOLETE [ver=%x net=%x]", version, netfs->version);
		return FSCACHE_CHECKAUX_OBSOLETE;
	}

	_leave(" = OKAY");
	return FSCACHE_CHECKAUX_OKAY;
}