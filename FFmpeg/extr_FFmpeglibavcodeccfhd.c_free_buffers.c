#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ ** l_h; int /*<<< orphan*/ ** subband; int /*<<< orphan*/  idwt_tmp; int /*<<< orphan*/  idwt_buf; } ;
struct TYPE_4__ {scalar_t__ a_width; scalar_t__ a_height; TYPE_3__* plane; } ;
typedef  TYPE_1__ CFHDContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_buffers(CFHDContext *s)
{
    int i, j;

    for (i = 0; i < FF_ARRAY_ELEMS(s->plane); i++) {
        av_freep(&s->plane[i].idwt_buf);
        av_freep(&s->plane[i].idwt_tmp);

        for (j = 0; j < 9; j++)
            s->plane[i].subband[j] = NULL;

        for (j = 0; j < 8; j++)
            s->plane[i].l_h[j] = NULL;
    }
    s->a_height = 0;
    s->a_width  = 0;
}