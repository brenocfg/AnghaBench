#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* search ) (TYPE_1__*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  map_name; int /*<<< orphan*/  modify; } ;
typedef  TYPE_1__ mnt_map ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_MAP ; 
 int /*<<< orphan*/  mapc_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
search_map(mnt_map *m, char *key, char **valp)
{
  int rc;

  do {
    rc = (*m->search) (m, m->map_name, key, valp, &m->modify);
    if (rc < 0) {
      plog(XLOG_MAP, "Re-synchronizing cache for map %s", m->map_name);
      mapc_sync(m);
    }
  } while (rc < 0);

  return rc;
}