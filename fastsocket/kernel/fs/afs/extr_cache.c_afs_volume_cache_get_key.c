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
typedef  int uint16_t ;
struct afs_volume {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t afs_volume_cache_get_key(const void *cookie_netfs_data,
					void *buffer, uint16_t bufmax)
{
	const struct afs_volume *volume = cookie_netfs_data;
	uint16_t klen;

	_enter("{%u},%p,%u", volume->type, buffer, bufmax);

	klen = sizeof(volume->type);
	if (klen > bufmax)
		return 0;

	memcpy(buffer, &volume->type, sizeof(volume->type));

	_leave(" = %u", klen);
	return klen;

}