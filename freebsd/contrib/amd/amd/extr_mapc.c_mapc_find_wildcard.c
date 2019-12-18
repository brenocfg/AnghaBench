#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * wildcard; } ;
typedef  TYPE_1__ mnt_map ;

/* Variables and functions */
 int search_map (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wildcard ; 

__attribute__((used)) static void
mapc_find_wildcard(mnt_map *m)
{
  /*
   * Attempt to find the wildcard entry
   */
  int rc = search_map(m, wildcard, &m->wildcard);

  if (rc != 0)
    m->wildcard = NULL;
}