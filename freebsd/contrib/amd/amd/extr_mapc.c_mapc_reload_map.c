#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int (* mtime ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ modify; scalar_t__ reloads; int (* reload ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * wildcard; int /*<<< orphan*/  map_name; scalar_t__ kvhash; scalar_t__ nentries; } ;
typedef  TYPE_1__ mnt_map ;
typedef  int /*<<< orphan*/  kv ;

/* Variables and functions */
 int NKVHASH ; 
 int /*<<< orphan*/  XFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 scalar_t__ do_mapc_reload ; 
 int /*<<< orphan*/  mapc_add_kv ; 
 int /*<<< orphan*/  mapc_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mapc_clear_kvhash (int /*<<< orphan*/ **) ; 
 int mapc_search (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wildcard ; 

__attribute__((used)) static int
mapc_reload_map(mnt_map *m)
{
  int error, ret = 0;
  kv *maphash[NKVHASH];
  time_t t;

  error = (*m->mtime) (m, m->map_name, &t);
  if (error) {
    t = m->modify;
  }

  /*
   * skip reloading maps that have not been modified, unless
   * amq -f was used (do_mapc_reload is 0)
   */
  if (m->reloads != 0 && do_mapc_reload != 0) {
    if (t <= m->modify) {
      plog(XLOG_INFO, "reload of map %s is not needed (in sync)", m->map_name);
      dlog("map %s last load time is %d, last modify time is %d",
	   m->map_name, (int) m->modify, (int) t);
      return ret;
    }
  }

  /* copy the old hash and zero the map */
  memcpy((voidp) maphash, (voidp) m->kvhash, sizeof(m->kvhash));
  memset((voidp) m->kvhash, 0, sizeof(m->kvhash));

  dlog("calling map reload on %s", m->map_name);
  m->nentries = 0;
  error = (*m->reload) (m, m->map_name, mapc_add_kv);
  if (error) {
    if (m->reloads == 0)
      plog(XLOG_FATAL, "first time load of map %s failed!", m->map_name);
    else
      plog(XLOG_ERROR, "reload of map %s failed - using old values",
	   m->map_name);
    mapc_clear(m);
    memcpy((voidp) m->kvhash, (voidp) maphash, sizeof(m->kvhash));
  } else {
    if (m->reloads++ == 0)
      plog(XLOG_INFO, "first time load of map %s succeeded", m->map_name);
    else
      plog(XLOG_INFO, "reload #%d of map %s succeeded",
	   m->reloads, m->map_name);
    mapc_clear_kvhash(maphash);
    if (m->wildcard) {
       XFREE(m->wildcard);
       m->wildcard = NULL;
    }
    m->modify = t;
    ret = 1;
  }

  dlog("calling mapc_search for wildcard");
  error = mapc_search(m, wildcard, &m->wildcard);
  if (error)
    m->wildcard = NULL;
  return ret;
}