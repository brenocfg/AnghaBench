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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PIXELS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void v210_planar_unpack_c(const uint32_t *src, uint16_t *y, uint16_t *u, uint16_t *v, int width)
{
    uint32_t val;
    int i;

    for( i = 0; i < width-5; i += 6 ){
        READ_PIXELS(u, y, v);
        READ_PIXELS(y, u, y);
        READ_PIXELS(v, y, u);
        READ_PIXELS(y, v, y);
    }
}