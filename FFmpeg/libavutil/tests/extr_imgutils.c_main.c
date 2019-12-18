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
typedef  int int64_t ;

/* Variables and functions */
 int UINT_MAX ; 
 int av_image_check_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(void)
{
    int64_t x, y;

    for (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        for (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            int ret = av_image_check_size(x, y, 0, NULL);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }

    return 0;
}