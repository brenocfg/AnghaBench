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
 int ENOENT ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*,char*,int /*<<< orphan*/ ) ; 
 int hesiod_search (int /*<<< orphan*/ *,char*,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 

int
hesiod_isup(mnt_map *m, char *map)
{
  int error;
  char *val;
  time_t mtime;
  static int last_status = 1;	/* assume up by default */

  error = hesiod_search(m, map, "/defaults", &val, &mtime);
  dlog("hesiod_isup(%s): %s", map, strerror(error));
  if (error != 0 && error != ENOENT) {
    plog(XLOG_ERROR,
	 "hesiod_isup: error getting `/defaults' entry in map %s: %m", map);
    last_status = 0;
    return 0;			/* Hesiod is down */
  }
  if (last_status == 0) {	/* if was down before */
    plog(XLOG_INFO, "hesiod_isup: Hesiod came back up for map %s", map);
    last_status = 1;
  }
  return 1;			/* Hesiod is up */
}