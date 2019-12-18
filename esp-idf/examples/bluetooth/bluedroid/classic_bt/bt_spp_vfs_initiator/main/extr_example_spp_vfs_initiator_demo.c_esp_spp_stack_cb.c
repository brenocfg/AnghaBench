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
typedef  int /*<<< orphan*/  esp_spp_cb_param_t ;
typedef  int /*<<< orphan*/  esp_spp_cb_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_spp_cb ; 
 int /*<<< orphan*/  spp_task_work_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esp_spp_stack_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    spp_task_work_dispatch(esp_spp_cb, event, param, sizeof(esp_spp_cb_param_t), NULL);
}