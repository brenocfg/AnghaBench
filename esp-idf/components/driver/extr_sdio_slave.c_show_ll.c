#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stqe_next; } ;
struct TYPE_6__ {TYPE_1__ qe; int /*<<< orphan*/  buf; int /*<<< orphan*/  owner; int /*<<< orphan*/  eof; int /*<<< orphan*/  length; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ lldesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGI (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static inline void show_ll(lldesc_t *item)
{
    ESP_EARLY_LOGI(TAG, "=> %p: size: %d(%d), eof: %d, owner: %d", item, item->size, item->length, item->eof, item->owner);
    ESP_EARLY_LOGI(TAG, "   buf: %p, stqe_next: %p", item->buf, item->qe.stqe_next);
}