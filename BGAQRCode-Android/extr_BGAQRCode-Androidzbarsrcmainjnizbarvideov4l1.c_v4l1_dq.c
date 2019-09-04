#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ iomode; int fd; } ;
typedef  TYPE_1__ zbar_video_t ;
struct TYPE_8__ {int srcidx; scalar_t__ datalen; scalar_t__ data; } ;
typedef  TYPE_2__ zbar_image_t ;
typedef  scalar_t__ video_iomode_t ;

/* Variables and functions */
 scalar_t__ VIDEO_MMAP ; 
 int /*<<< orphan*/  VIDIOCSYNC ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ read (int,void*,scalar_t__) ; 
 TYPE_2__* video_dq_image (TYPE_1__*) ; 

__attribute__((used)) static zbar_image_t *v4l1_dq (zbar_video_t *vdo)
{
    video_iomode_t iomode = vdo->iomode;
    int fd = vdo->fd;
    zbar_image_t *img = video_dq_image(vdo);
    if(!img)
        return(NULL);

    if(iomode == VIDEO_MMAP) {
        int frame = img->srcidx;
        if(ioctl(fd, VIDIOCSYNC, &frame) < 0)
            return(NULL);
    }
    else if(read(fd, (void*)img->data, img->datalen) != img->datalen)
        return(NULL);

    return(img);
}