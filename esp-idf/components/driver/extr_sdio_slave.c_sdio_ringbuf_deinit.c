#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * remain_cnt; } ;
typedef  TYPE_1__ sdio_ringbuf_t ;

/* Variables and functions */
 TYPE_1__ SDIO_RINGBUF_INITIALIZER () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdio_ringbuf_deinit(sdio_ringbuf_t* buf)
{
    if (buf->remain_cnt != NULL) vSemaphoreDelete(buf->remain_cnt);
    if (buf->data != NULL) free(buf->data);
    *buf = SDIO_RINGBUF_INITIALIZER();
}