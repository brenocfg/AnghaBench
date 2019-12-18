#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  context; } ;
struct TYPE_7__ {char* name; } ;
typedef  int /*<<< orphan*/  Hash_Search ;
typedef  TYPE_1__ Hash_Entry ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 int /*<<< orphan*/  Hash_DeleteEntry (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* Hash_EnumFirst (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* Hash_EnumNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* get_cached_realpaths () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
purge_cached_realpaths(void)
{
    GNode *cache = get_cached_realpaths();
    Hash_Entry *he, *nhe;
    Hash_Search hs;

    he = Hash_EnumFirst(&cache->context, &hs);
    while (he) {
	nhe = Hash_EnumNext(&hs);
	if (he->name[0] != '/') {
	    if (DEBUG(DIR))
		fprintf(stderr, "cached_realpath: purging %s\n", he->name);
	    Hash_DeleteEntry(&cache->context, he);
	}
	he = nhe;
    }
}