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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rotate_faulty_loco(uint8_t *data, int width, int height, int stride)
{
    int y;

    for (y=1; y<height; y++) {
        if (width>=y) {
            memmove(data + y*stride,
                    data + y*(stride + 1),
                    (width-y));
            if (y+1 < height)
                memmove(data + y*stride + (width-y),
                        data + (y+1)*stride, y);
        }
    }
}