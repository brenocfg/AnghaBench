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
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_1__ hb_buffer_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ *,int) ; 

int hb_list_bytes( hb_list_t * l )
{
    hb_buffer_t * buf;
    int           ret;
    int           i;

    ret = 0;
    for( i = 0; i < hb_list_count( l ); i++ )
    {
        buf  = hb_list_item( l, i );
        ret += buf->size - buf->offset;
    }

    return ret;
}