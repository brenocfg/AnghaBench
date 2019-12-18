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
struct cifs_tcon {int /*<<< orphan*/  resource_id; } ;
struct cifs_fscache_super_auxdata {int /*<<< orphan*/  resource_id; } ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,struct cifs_fscache_super_auxdata*,int) ; 
 int /*<<< orphan*/  memset (struct cifs_fscache_super_auxdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t
cifs_fscache_super_get_aux(const void *cookie_netfs_data, void *buffer,
			   uint16_t maxbuf)
{
	struct cifs_fscache_super_auxdata auxdata;
	const struct cifs_tcon *tcon = cookie_netfs_data;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.resource_id = tcon->resource_id;

	if (maxbuf > sizeof(auxdata))
		maxbuf = sizeof(auxdata);

	memcpy(buffer, &auxdata, maxbuf);

	return maxbuf;
}