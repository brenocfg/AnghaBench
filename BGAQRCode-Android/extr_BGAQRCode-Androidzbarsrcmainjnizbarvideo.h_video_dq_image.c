#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dq_image; } ;
typedef  TYPE_1__ zbar_video_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ zbar_image_t ;

/* Variables and functions */
 scalar_t__ video_unlock (TYPE_1__*) ; 

__attribute__((used)) static inline zbar_image_t *video_dq_image (zbar_video_t *vdo)
{
    zbar_image_t *img = vdo->dq_image;
    if(img) {
        vdo->dq_image = img->next;
        img->next = NULL;
    }
    if(video_unlock(vdo))
        /* FIXME reclaim image */
        return(NULL);
    return(img);
}