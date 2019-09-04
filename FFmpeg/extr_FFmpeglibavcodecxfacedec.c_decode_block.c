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
typedef  int /*<<< orphan*/  BigInt ;

/* Variables and functions */
#define  XFACE_COLOR_BLACK 129 
#define  XFACE_COLOR_WHITE 128 
 int XFACE_WIDTH ; 
 int /*<<< orphan*/ ** ff_xface_probranges_per_level ; 
 int /*<<< orphan*/  pop_greys (int /*<<< orphan*/ *,char*,int,int) ; 
 int pop_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_block(BigInt *b, char *bitmap, int w, int h, int level)
{
    switch (pop_integer(b, &ff_xface_probranges_per_level[level][0])) {
    case XFACE_COLOR_WHITE:
        return;
    case XFACE_COLOR_BLACK:
        pop_greys(b, bitmap, w, h);
        return;
    default:
        w /= 2;
        h /= 2;
        level++;
        decode_block(b, bitmap,                       w, h, level);
        decode_block(b, bitmap + w,                   w, h, level);
        decode_block(b, bitmap + h * XFACE_WIDTH,     w, h, level);
        decode_block(b, bitmap + w + h * XFACE_WIDTH, w, h, level);
        return;
    }
}