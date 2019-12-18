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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  mnt_map ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_open (char*,scalar_t__*) ; 
 int file_search_or_reload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char**,int /*<<< orphan*/ *) ; 

int
file_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  time_t t;
  FILE *mapf = file_open(map, &t);

  if (mapf) {
    int error;
    if (*tp < t) {
      *tp = t;
      error = -1;
    } else {
      error = file_search_or_reload(m, mapf, map, key, pval, NULL);
    }
    (void) fclose(mapf);
    return error;
  }
  return errno;
}