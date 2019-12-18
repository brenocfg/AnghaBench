#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int size; int alloc; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ hb_buffer_t ;

/* Variables and functions */

void hb_buffer_swap_copy( hb_buffer_t *src, hb_buffer_t *dst )
{
    uint8_t *data  = dst->data;
    int      size  = dst->size;
    int      alloc = dst->alloc;

    *dst = *src;

    src->data  = data;
    src->size  = size;
    src->alloc = alloc;
}