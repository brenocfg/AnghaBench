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
struct TYPE_2__ {int /*<<< orphan*/  peer_bdaddr; scalar_t__ peer_name; } ;

/* Variables and functions */
 char* BTM_SecReadDevName (int /*<<< orphan*/ ) ; 
 TYPE_1__ bta_dm_search_cb ; 

__attribute__((used)) static char *bta_dm_get_remname(void)
{
    char *p_name = (char *)bta_dm_search_cb.peer_name;
    char *p_temp;

    /* If the name isn't already stored, try retrieving from BTM */
    if (*p_name == '\0') {
        if ((p_temp = BTM_SecReadDevName(bta_dm_search_cb.peer_bdaddr)) != NULL) {
            p_name = p_temp;
        }
    }
    return p_name;
}