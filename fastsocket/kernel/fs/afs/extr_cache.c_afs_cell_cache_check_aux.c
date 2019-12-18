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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;

/* Variables and functions */
 int FSCACHE_CHECKAUX_OKAY ; 
 int /*<<< orphan*/  _leave (char*) ; 

__attribute__((used)) static enum fscache_checkaux afs_cell_cache_check_aux(void *cookie_netfs_data,
						      const void *buffer,
						      uint16_t buflen)
{
	_leave(" = OKAY");
	return FSCACHE_CHECKAUX_OKAY;
}