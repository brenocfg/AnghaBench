#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int width; int height; int row; int col; int /*<<< orphan*/ * data; int /*<<< orphan*/ * enc; } ;
struct TYPE_5__ {int cols; int rows; int block_width; int image_width; int block_height; int image_height; } ;
typedef  TYPE_1__ FlashSV2Context ;
typedef  TYPE_2__ Block ;

/* Variables and functions */

__attribute__((used)) static void init_blocks(FlashSV2Context * s, Block * blocks,
                        uint8_t * encbuf, uint8_t * databuf)
{
    int row, col;
    Block *b;
    for (col = 0; col < s->cols; col++) {
        for (row = 0; row < s->rows; row++) {
            b = blocks + (col + row * s->cols);
            b->width = (col < s->cols - 1) ?
                s->block_width :
                s->image_width - col * s->block_width;

            b->height = (row < s->rows - 1) ?
                s->block_height :
                s->image_height - row * s->block_height;

            b->row   = row;
            b->col   = col;
            b->enc   = encbuf;
            b->data  = databuf;
            encbuf  += b->width * b->height * 3;
            databuf += !databuf ? 0 : b->width * b->height * 6;
        }
    }
}