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
struct TYPE_5__ {scalar_t__ iomode; } ;
typedef  TYPE_1__ zbar_video_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ VIDEO_MMAP ; 
 scalar_t__ v4l1_mmap_buffers (TYPE_1__*) ; 
 scalar_t__ v4l1_set_format (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v4l1_init (zbar_video_t *vdo,
                      uint32_t fmt)
{
    if(v4l1_set_format(vdo, fmt))
        return(-1);
    if(vdo->iomode == VIDEO_MMAP && v4l1_mmap_buffers(vdo))
        return(-1);
    return(0);
}