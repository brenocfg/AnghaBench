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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

__attribute__((used)) static void
find_tongue(uint16_t* const pixels,
            int       const w,
            int       const linesize,
            int       const row,
            int *     const presentP,
            int *     const leftEdgeP,
            int *     const rightEdgeP)
{
    int i;

    for (i = 0; i < w && pixels[row * linesize + i * 4 + 0] == 0; i++)
        ;

    if (i >= w) {
        *presentP = 0;
    } else {
        int j;
        int const leftEdge = i;

        *presentP = 1;

        for (j = w - 1; j >= leftEdge && pixels[row * linesize + j * 4 + 0] == 0; j--)
            ;

        *rightEdgeP = j;
        *leftEdgeP = leftEdge;
    }
}