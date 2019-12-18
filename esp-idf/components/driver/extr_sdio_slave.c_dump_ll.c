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
typedef  int /*<<< orphan*/  lldesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  qe ; 
 int /*<<< orphan*/  show_ll (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __attribute((unused)) dump_ll(lldesc_t *queue)
{
    int cnt = 0;
    lldesc_t *item = queue;
    while (item != NULL) {
        cnt++;
        show_ll(item);
        item = STAILQ_NEXT(item, qe);
    }
    ESP_EARLY_LOGI(TAG, "total: %d", cnt);
}