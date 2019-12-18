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
struct TYPE_5__ {struct TYPE_5__* work; struct TYPE_5__* cache; struct TYPE_5__* fds; int /*<<< orphan*/  lock; struct TYPE_5__* fs; } ;
typedef  TYPE_1__ esp_spiffs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_unmount (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_spiffs_free(esp_spiffs_t ** efs)
{
    esp_spiffs_t * e = *efs;
    if (*efs == NULL) {
        return;
    }
    *efs = NULL;

    if (e->fs) {
        SPIFFS_unmount(e->fs);
        free(e->fs);
    }
    vSemaphoreDelete(e->lock);
    free(e->fds);
    free(e->cache);
    free(e->work);
    free(e);
}