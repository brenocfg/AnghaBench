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
struct TYPE_3__ {int /*<<< orphan*/  endpoints; } ;
typedef  TYPE_1__ protocomm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 

protocomm_t *protocomm_new(void)
{
    protocomm_t *pc;

    pc = (protocomm_t *) calloc(1, sizeof(protocomm_t));
    if (!pc) {
       ESP_LOGE(TAG, "Error allocating protocomm");
       return NULL;
    }
    SLIST_INIT(&pc->endpoints);

    return pc;
}