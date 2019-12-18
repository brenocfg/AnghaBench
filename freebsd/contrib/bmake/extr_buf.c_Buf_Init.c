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
struct TYPE_3__ {int size; scalar_t__* buffer; scalar_t__ count; } ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 int BUF_DEF_SIZE ; 
 scalar_t__* bmake_malloc (int) ; 

void
Buf_Init(Buffer *bp, int size)
{
    if (size <= 0) {
	size = BUF_DEF_SIZE;
    }
    bp->size = size;
    bp->count = 0;
    bp->buffer = bmake_malloc(size);
    *bp->buffer = 0;
}