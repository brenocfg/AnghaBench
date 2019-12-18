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

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HES_PREFIX ; 
 int /*<<< orphan*/  HES_PREFLEN ; 
 scalar_t__ NSTREQ (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 int /*<<< orphan*/  hesiod_context ; 
 scalar_t__ hesiod_init (int /*<<< orphan*/ *) ; 

int
amu_hesiod_init(mnt_map *m, char *map, time_t *tp)
{
  dlog("amu_hesiod_init(%s)", map);
  *tp = 0;

#ifdef HAVE_HESIOD_INIT
  if (!hesiod_context && hesiod_init(&hesiod_context) != 0)
    return ENOENT;
#endif /* HAVE_HESIOD_INIT */

  return NSTREQ(map, HES_PREFIX, HES_PREFLEN) ? 0 : ENOENT;
}