#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  emms_c () ; 

int avcodec_default_execute(AVCodecContext *c, int (*func)(AVCodecContext *c2, void *arg2), void *arg, int *ret, int count, int size)
{
    int i;

    for (i = 0; i < count; i++) {
        int r = func(c, (char *)arg + i * size);
        if (ret)
            ret[i] = r;
    }
    emms_c();
    return 0;
}