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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  mnt_map ;

/* Variables and functions */
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,char*,char*) ; 
 int errno ; 
 int exec_check_perm (char*) ; 
 int exec_map_open (char*,char*) ; 
 int exec_parse_qanswer (int /*<<< orphan*/ *,int,char*,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 scalar_t__ logfp ; 

int
exec_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  int mapfd, ret;

  if ((ret = exec_check_perm(map)) != 0) {
    return ret;
  }

  if (!key)
    return 0;

  if (logfp)
    fflush(logfp);
  dlog("exec_search \"%s\", key: \"%s\"", map, key);
  mapfd = exec_map_open(map, key);

  if (mapfd >= 0) {
    if (tp)
      *tp = clocktime(NULL);

    return exec_parse_qanswer(m, mapfd, map, key, pval, tp);
  }

  return errno;
}