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
typedef  int uint8_t ;
struct TYPE_3__ {int* buf; int size; int val; scalar_t__ pos; } ;
typedef  TYPE_1__ bitbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bits_init(bitbuf_t *bb, uint8_t* buf, int bufsize, int clear)
{
    bb->pos = 0;
    bb->buf = buf;
    bb->size = bufsize;
    bb->val = (bb->buf[0] << 24) | (bb->buf[1] << 16) |
              (bb->buf[2] << 8) | bb->buf[3];
    if (clear)
        memset(bb->buf, 0, bufsize);
    bb->size = bufsize;
}