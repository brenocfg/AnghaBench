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
struct TYPE_6__ {int fd; int num_images; TYPE_2__** images; int /*<<< orphan*/  qlock; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ zbar_video_t ;
struct TYPE_7__ {int srcidx; TYPE_1__* src; int /*<<< orphan*/  cleanup; scalar_t__ refcnt; } ;
typedef  TYPE_2__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_MOD_VIDEO ; 
 int ZBAR_VIDEO_IMAGES_MAX ; 
 int /*<<< orphan*/  _zbar_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_video_recycle_image ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* zbar_image_create () ; 
 int /*<<< orphan*/  zbar_video_destroy (TYPE_1__*) ; 

zbar_video_t *zbar_video_create ()
{
    zbar_video_t *vdo = calloc(1, sizeof(zbar_video_t));
    int i;
    if(!vdo)
        return(NULL);
    err_init(&vdo->err, ZBAR_MOD_VIDEO);
    vdo->fd = -1;

    (void)_zbar_mutex_init(&vdo->qlock);

    /* pre-allocate images */
    vdo->num_images = ZBAR_VIDEO_IMAGES_MAX;
    vdo->images = calloc(ZBAR_VIDEO_IMAGES_MAX, sizeof(zbar_image_t*));
    if(!vdo->images) {
        zbar_video_destroy(vdo);
        return(NULL);
    }

    for(i = 0; i < ZBAR_VIDEO_IMAGES_MAX; i++) {
        zbar_image_t *img = vdo->images[i] = zbar_image_create();
        if(!img) {
            zbar_video_destroy(vdo);
            return(NULL);
        }
        img->refcnt = 0;
        img->cleanup = _zbar_video_recycle_image;
        img->srcidx = i;
        img->src = vdo;
    }

    return(vdo);
}