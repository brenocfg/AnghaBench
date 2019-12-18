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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ apb_change_t ;
typedef  int /*<<< orphan*/  apb_change_ev_t ;

/* Variables and functions */
 TYPE_1__* apb_change_callbacks ; 
 int /*<<< orphan*/  apb_change_lock ; 
 int /*<<< orphan*/  initApbChangeCallback () ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void triggerApbChangeCallback(apb_change_ev_t ev_type, uint32_t old_apb, uint32_t new_apb){
    initApbChangeCallback();
    xSemaphoreTake(apb_change_lock, portMAX_DELAY);
    apb_change_t * r = apb_change_callbacks;
    while(r != NULL){
        r->cb(r->arg, ev_type, old_apb, new_apb);
        r=r->next;
    }
    xSemaphoreGive(apb_change_lock);
}