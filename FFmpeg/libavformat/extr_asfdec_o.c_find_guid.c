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
typedef  int /*<<< orphan*/  ff_asf_guid ;
struct TYPE_5__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ GUIDParseTable ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* gdef ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const GUIDParseTable *find_guid(ff_asf_guid guid)
{
    int j, ret;
    const GUIDParseTable *g;

    swap_guid(guid);
    g = gdef;
    for (j = 0; j < FF_ARRAY_ELEMS(gdef); j++) {
        if (!(ret = memcmp(guid, g->guid, sizeof(g->guid))))
            return g;
        g++;
    }

    return NULL;
}