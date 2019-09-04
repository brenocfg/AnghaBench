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
struct TYPE_3__ {scalar_t__ iomode; int /*<<< orphan*/  num_images; } ;
typedef  TYPE_1__ zbar_video_t ;

/* Variables and functions */
 scalar_t__ VIDEO_READWRITE ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int v4l1_probe_iomode (zbar_video_t *vdo)
{
    vdo->iomode = VIDEO_READWRITE;
#ifdef HAVE_SYS_MMAN_H
    struct video_mbuf vbuf;
    memset(&vbuf, 0, sizeof(vbuf));
    if(ioctl(vdo->fd, VIDIOCGMBUF, &vbuf) < 0) {
        if(errno != EINVAL)
            return(err_capture(vdo, SEV_ERROR, ZBAR_ERR_SYSTEM, __func__,
                               "querying video frame buffers (VIDIOCGMBUF)"));
        /* not supported */
        return(0);
    }
    if(!vbuf.frames || !vbuf.size)
        return(0);
    vdo->iomode = VIDEO_MMAP;
    if(vdo->num_images > vbuf.frames)
        vdo->num_images = vbuf.frames;
#endif
    zprintf(1, "using %d images in %s mode\n", vdo->num_images,
            (vdo->iomode == VIDEO_READWRITE) ? "READ" : "MMAP");
    return(0);
}