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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void drawline(AVFrame *pic, int x, int y, int len, int step)
{
    int i;
    uint8_t *p = pic->data[0] + y*pic->linesize[0] + x*3;

    for (i = 0; i < len; i++) {
        memcpy(p, "\x00\xff\x00", 3);
        p += step;
    }
}