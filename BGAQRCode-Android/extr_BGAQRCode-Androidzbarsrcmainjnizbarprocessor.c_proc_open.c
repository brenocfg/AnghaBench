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
struct TYPE_4__ {scalar_t__ video; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int _zbar_processor_open (TYPE_1__*,char*,int,int) ; 
 int zbar_video_get_height (scalar_t__) ; 
 int zbar_video_get_width (scalar_t__) ; 

__attribute__((used)) static inline int proc_open (zbar_processor_t *proc)
{
    /* arbitrary default */
    int width = 640, height = 480;
    if(proc->video) {
        width = zbar_video_get_width(proc->video);
        height = zbar_video_get_height(proc->video);
    }
    return(_zbar_processor_open(proc, "zbar barcode reader", width, height));
}