#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {scalar_t__ size; TYPE_1__ s; int /*<<< orphan*/  f; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ FRAME_BUF ; 
 int /*<<< orphan*/  hb_buffer_init_planes (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int hb_buffer_copy(hb_buffer_t * dst, const hb_buffer_t * src)
{
    if (src == NULL || dst == NULL)
        return -1;

    if ( dst->size < src->size )
        return -1;

    memcpy( dst->data, src->data, src->size );
    dst->s = src->s;
    dst->f = src->f;
    if (dst->s.type == FRAME_BUF)
        hb_buffer_init_planes(dst);

    return 0;
}