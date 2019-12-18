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
typedef  int /*<<< orphan*/  tBTA_DM_MSG ;
typedef  int /*<<< orphan*/  tBTA_DM_API_SEARCH ;
struct TYPE_2__ {int /*<<< orphan*/ * p_search_queue; } ;

/* Variables and functions */
 TYPE_1__ bta_dm_search_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ osi_malloc (int) ; 

void bta_dm_queue_search (tBTA_DM_MSG *p_data)
{
    if (bta_dm_search_cb.p_search_queue) {
        osi_free(bta_dm_search_cb.p_search_queue);
    }

    bta_dm_search_cb.p_search_queue = (tBTA_DM_MSG *)osi_malloc(sizeof(tBTA_DM_API_SEARCH));
    memcpy(bta_dm_search_cb.p_search_queue, p_data, sizeof(tBTA_DM_API_SEARCH));

}