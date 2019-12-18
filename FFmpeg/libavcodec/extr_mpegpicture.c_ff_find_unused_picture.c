#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ needs_realloc; } ;
typedef  TYPE_1__ Picture ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int MAX_PICTURE_COUNT ; 
 int /*<<< orphan*/  ff_free_picture_tables (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int find_unused_picture (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

int ff_find_unused_picture(AVCodecContext *avctx, Picture *picture, int shared)
{
    int ret = find_unused_picture(avctx, picture, shared);

    if (ret >= 0 && ret < MAX_PICTURE_COUNT) {
        if (picture[ret].needs_realloc) {
            picture[ret].needs_realloc = 0;
            ff_free_picture_tables(&picture[ret]);
            ff_mpeg_unref_picture(avctx, &picture[ret]);
        }
    }
    return ret;
}