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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ vector_desc_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  VECDESC_FL_RESERVED ; 
 TYPE_1__* get_desc_for_int (int,int) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int portNUM_PROCESSORS ; 
 int /*<<< orphan*/  spinlock ; 

esp_err_t esp_intr_reserve(int intno, int cpu)
{
    if (intno>31) return ESP_ERR_INVALID_ARG;
    if (cpu>=portNUM_PROCESSORS) return ESP_ERR_INVALID_ARG;

    portENTER_CRITICAL(&spinlock);
    vector_desc_t *vd=get_desc_for_int(intno, cpu);
    if (vd==NULL) {
        portEXIT_CRITICAL(&spinlock);
        return ESP_ERR_NO_MEM;
    }
    vd->flags=VECDESC_FL_RESERVED;
    portEXIT_CRITICAL(&spinlock);

    return ESP_OK;
}