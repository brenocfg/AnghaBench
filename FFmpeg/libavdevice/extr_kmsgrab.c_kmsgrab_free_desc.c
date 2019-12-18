#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* objects; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ AVDRMFrameDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kmsgrab_free_desc(void *opaque, uint8_t *data)
{
    AVDRMFrameDescriptor *desc = (AVDRMFrameDescriptor*)data;

    close(desc->objects[0].fd);

    av_free(desc);
}