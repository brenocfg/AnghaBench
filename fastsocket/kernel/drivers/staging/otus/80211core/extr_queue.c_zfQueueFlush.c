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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
struct zsQueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * zfQueueGet (int /*<<< orphan*/ *,struct zsQueue*) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zfQueueFlush(zdev_t* dev, struct zsQueue* q)
{
    zbuf_t* buf;

    while ((buf = zfQueueGet(dev, q)) != NULL)
    {
        zfwBufFree(dev, buf, 0);
    }

    return;
}