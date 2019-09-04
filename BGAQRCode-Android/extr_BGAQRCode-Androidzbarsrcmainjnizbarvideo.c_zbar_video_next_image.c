#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int num_images; int /*<<< orphan*/  datalen; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; TYPE_2__* shadow_image; TYPE_2__* (* dq ) (TYPE_1__*) ;int /*<<< orphan*/  frame; int /*<<< orphan*/  active; } ;
typedef  TYPE_1__ zbar_video_t ;
struct TYPE_16__ {unsigned int seq; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  datalen; scalar_t__ data; int /*<<< orphan*/  format; TYPE_1__* src; scalar_t__ refcnt; struct TYPE_16__* next; } ;
typedef  TYPE_2__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_refcnt (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _zbar_video_recycle_image (TYPE_2__*) ; 
 int /*<<< orphan*/  _zbar_video_recycle_shadow (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub1 (TYPE_1__*) ; 
 scalar_t__ video_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  video_unlock (TYPE_1__*) ; 
 TYPE_2__* zbar_image_create () ; 
 int /*<<< orphan*/  zbar_image_set_size (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zbar_image_t *zbar_video_next_image (zbar_video_t *vdo)
{
    unsigned frame;
    zbar_image_t *img;

    if(video_lock(vdo))
        return(NULL);
    if(!vdo->active) {
        video_unlock(vdo);
        return(NULL);
    }

    frame = vdo->frame++;
    img = vdo->dq(vdo);
    if(img) {
        img->seq = frame;
        if(vdo->num_images < 2) {
            /* return a *copy* of the video image and immediately recycle
             * the driver's buffer to avoid deadlocking the resources
             */
            zbar_image_t *tmp = img;
            video_lock(vdo);
            img = vdo->shadow_image;
            vdo->shadow_image = (img) ? img->next : NULL;
            video_unlock(vdo);
                
            if(!img) {
                img = zbar_image_create();
                assert(img);
                img->refcnt = 0;
                img->src = vdo;
                /* recycle the shadow images */

                img->format = vdo->format;
                zbar_image_set_size(img, vdo->width, vdo->height);
                img->datalen = vdo->datalen;
                img->data = malloc(vdo->datalen);
            }
            img->cleanup = _zbar_video_recycle_shadow;
            img->seq = frame;
            memcpy((void*)img->data, tmp->data, img->datalen);
            _zbar_video_recycle_image(tmp);
        }
        else
            img->cleanup = _zbar_video_recycle_image;
        _zbar_image_refcnt(img, 1);
    }
    return(img);
}