#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {scalar_t__ map_data; } ;
typedef  TYPE_1__ mnt_map ;
typedef  int /*<<< orphan*/  ALD ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ amu_ldap_rebind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*) ; 
 scalar_t__ get_ldap_timestamp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

int
amu_ldap_mtime(mnt_map *m, char *map, time_t *ts)
{
  ALD *aldh = (ALD *) (m->map_data);

  if (aldh == NULL) {
    dlog("LDAP panic: unable to find map data\n");
    return (ENOENT);
  }
  if (amu_ldap_rebind(aldh)) {
    return (ENOENT);
  }
  if (get_ldap_timestamp(aldh, map, ts)) {
    return (ENOENT);
  }
  return (0);
}