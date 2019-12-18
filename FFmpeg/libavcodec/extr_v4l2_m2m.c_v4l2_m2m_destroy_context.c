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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  refsync; int /*<<< orphan*/  capture; } ;
typedef  TYPE_1__ V4L2m2mContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_v4l2_context_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void v4l2_m2m_destroy_context(void *opaque, uint8_t *context)
{
    V4L2m2mContext *s = (V4L2m2mContext*)context;

    ff_v4l2_context_release(&s->capture);
    sem_destroy(&s->refsync);

    close(s->fd);

    av_free(s);
}