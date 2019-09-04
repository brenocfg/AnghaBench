#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ intf; int /*<<< orphan*/  fd; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ zbar_video_t ;

/* Variables and functions */
 scalar_t__ VIDEO_INVALID ; 
 int _zbar_video_open (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  video_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  video_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_video_enable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ) ; 

int zbar_video_open (zbar_video_t *vdo,
                     const char *dev)
{
    char *ldev = NULL;
    int rc;
    zbar_video_enable(vdo, 0);
    video_lock(vdo);
    if(vdo->intf != VIDEO_INVALID) {
        if(vdo->cleanup) {
            vdo->cleanup(vdo);
            vdo->cleanup = NULL;
        }
        zprintf(1, "closed camera (fd=%d)\n", vdo->fd);
        vdo->intf = VIDEO_INVALID;
    }
    video_unlock(vdo);

    if(!dev)
        return(0);

    if((unsigned char)dev[0] < 0x10) {
        /* default linux device, overloaded for other platforms */
        int id = dev[0];
        dev = ldev = strdup("/dev/video0");
        ldev[10] = '0' + id;
    }

    rc = _zbar_video_open(vdo, dev);

    if(ldev)
        free(ldev);
    return(rc);
}