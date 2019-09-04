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
struct TYPE_5__ {int /*<<< orphan*/  src; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_free (TYPE_1__*) ; 
 int /*<<< orphan*/  _zbar_refcnt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static inline void _zbar_image_refcnt (zbar_image_t *img,
                                       int delta)
{
    if(!_zbar_refcnt(&img->refcnt, delta) && delta <= 0) {
        if(img->cleanup)
            img->cleanup(img);
        if(!img->src)
            _zbar_image_free(img);
    }
}