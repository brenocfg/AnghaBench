#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int width; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_7__ {TYPE_1__ rgb; } ;
typedef  TYPE_2__ ColorFloat ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 void* lrintf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_sono_rgb(AVFrame *sono, const ColorFloat *c, int idx)
{
    int x, w = sono->width;
    uint8_t *lp = sono->data[0] + idx * sono->linesize[0];

    for (x = 0; x < w; x++) {
        *lp++ = lrintf(c[x].rgb.r);
        *lp++ = lrintf(c[x].rgb.g);
        *lp++ = lrintf(c[x].rgb.b);
    }
}