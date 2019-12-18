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
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_3__ {scalar_t__ nentries; int /*<<< orphan*/ * wildcard; scalar_t__ kvhash; } ;
typedef  TYPE_1__ mnt_map ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapc_clear_kvhash (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mapc_clear(mnt_map *m)
{
  mapc_clear_kvhash(m->kvhash);

  /*
   * Zero the hash slots
   */
  memset((voidp) m->kvhash, 0, sizeof(m->kvhash));

  /*
   * Free the wildcard if it exists
   */
  XFREE(m->wildcard);
  m->wildcard = NULL;

  m->nentries = 0;
}