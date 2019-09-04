#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fd; scalar_t__ iomode; int num_images; unsigned long datalen; TYPE_3__** images; scalar_t__ buf; scalar_t__ buflen; } ;
typedef  TYPE_2__ zbar_video_t ;
struct TYPE_11__ {unsigned long datalen; scalar_t__ data; } ;
typedef  TYPE_3__ zbar_image_t ;
typedef  scalar_t__ video_iomode_t ;
typedef  int /*<<< orphan*/  vbuf ;
struct TYPE_9__ {unsigned long userptr; } ;
struct v4l2_buffer {int index; TYPE_1__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 scalar_t__ VIDEO_MMAP ; 
 scalar_t__ VIDEO_READWRITE ; 
 int /*<<< orphan*/  VIDIOC_DQBUF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 int /*<<< orphan*/  memset (struct v4l2_buffer*,int /*<<< orphan*/ ,int) ; 
 unsigned long read (int,void*,unsigned long) ; 
 TYPE_3__* video_dq_image (TYPE_2__*) ; 
 scalar_t__ video_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  zprintf (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static zbar_image_t *v4l2_dq (zbar_video_t *vdo)
{
    zbar_image_t *img;
    int fd = vdo->fd;

    if(vdo->iomode != VIDEO_READWRITE) {
        video_iomode_t iomode = vdo->iomode;
        if(video_unlock(vdo))
            return(NULL);

        struct v4l2_buffer vbuf;
        memset(&vbuf, 0, sizeof(vbuf));
        vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if(iomode == VIDEO_MMAP)
            vbuf.memory = V4L2_MEMORY_MMAP;
        else
            vbuf.memory = V4L2_MEMORY_USERPTR;

        if(ioctl(fd, VIDIOC_DQBUF, &vbuf) < 0)
            return(NULL);

        if(iomode == VIDEO_MMAP) {
            assert(vbuf.index >= 0);
            assert(vbuf.index < vdo->num_images);
            img = vdo->images[vbuf.index];
        }
        else {
            /* reverse map pointer back to image (FIXME) */
            assert(vbuf.m.userptr >= (unsigned long)vdo->buf);
            assert(vbuf.m.userptr < (unsigned long)(vdo->buf + vdo->buflen));
            int i = (vbuf.m.userptr - (unsigned long)vdo->buf) / vdo->datalen;
            assert(i >= 0);
            assert(i < vdo->num_images);
            img = vdo->images[i];
            assert(vbuf.m.userptr == (unsigned long)img->data);
        }
    }
    else {
        img = video_dq_image(vdo);
        if(!img)
            return(NULL);

        /* FIXME should read entire image */
        unsigned long datalen = read(fd, (void*)img->data, img->datalen);
        if(datalen < 0)
            return(NULL);
        else if(datalen != img->datalen)
            zprintf(0, "WARNING: read() size mismatch: 0x%lx != 0x%lx\n",
                    datalen, img->datalen);
    }
    return(img);
}