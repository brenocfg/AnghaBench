#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int n_uris; char const** uris; } ;
typedef  TYPE_1__ URITable ;
typedef  scalar_t__ LV2_URID_Map_Handle ;
typedef  int LV2_URID ;

/* Variables and functions */

__attribute__((used)) static const char *uri_table_unmap(LV2_URID_Map_Handle handle, LV2_URID urid)
{
    URITable *table = (URITable*)handle;

    if (urid > 0 && urid <= table->n_uris) {
        return table->uris[urid - 1];
    }

    return NULL;
}