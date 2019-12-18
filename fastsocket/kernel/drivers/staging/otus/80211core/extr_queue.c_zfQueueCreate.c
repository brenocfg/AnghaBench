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
typedef  int u16_t ;
struct zsQueueCell {int dummy; } ;
struct zsQueue {int size; int sizeMask; scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */
 scalar_t__ zfwMemAllocate (int /*<<< orphan*/ *,int) ; 

struct zsQueue* zfQueueCreate(zdev_t* dev, u16_t size)
{
    struct zsQueue* q;

    if ((q = (struct zsQueue*)zfwMemAllocate(dev, sizeof(struct zsQueue)
            + (sizeof(struct zsQueueCell)*(size-1)))) != NULL)
    {
        q->size = size;
        q->sizeMask = size-1;
        q->head = 0;
        q->tail = 0;
    }
    return q;
}