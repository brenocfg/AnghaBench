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
struct afs_cell {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_cell const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t afs_cell_cache_get_key(const void *cookie_netfs_data,
				       void *buffer, uint16_t bufmax)
{
	const struct afs_cell *cell = cookie_netfs_data;
	uint16_t klen;

	_enter("%p,%p,%u", cell, buffer, bufmax);

	klen = strlen(cell->name);
	if (klen > bufmax)
		return 0;

	memcpy(buffer, cell->name, klen);
	return klen;
}