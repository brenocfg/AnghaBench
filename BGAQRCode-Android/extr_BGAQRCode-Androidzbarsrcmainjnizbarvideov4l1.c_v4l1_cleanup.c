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
struct TYPE_3__ {int fd; } ;
typedef  TYPE_1__ zbar_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static int v4l1_cleanup (zbar_video_t *vdo)
{
#ifdef HAVE_SYS_MMAN_H
    /* FIXME should avoid holding onto mmap'd buffers so long? */
    if(vdo->iomode == VIDEO_MMAP && vdo->buf) {
        if(munmap(vdo->buf, vdo->buflen))
            return(err_capture(vdo, SEV_ERROR, ZBAR_ERR_SYSTEM, __func__,
                               "unmapping video frame buffers"));
        vdo->buf = NULL;
        /* FIXME reset image */
    }
#endif

    /* close open device */
    if(vdo->fd >= 0) {
        close(vdo->fd);
        vdo->fd = -1;
    }
    return(0);
}