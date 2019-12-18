#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  qsv_details; TYPE_1__ s; int /*<<< orphan*/  f; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ FRAME_BUF ; 
 TYPE_2__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_buffer_init_planes (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

hb_buffer_t * hb_buffer_dup( const hb_buffer_t * src )
{

    hb_buffer_t * buf;

    if ( src == NULL )
        return NULL;

    buf = hb_buffer_init( src->size );
    if ( buf )
    {
        memcpy( buf->data, src->data, src->size );
        buf->s = src->s;
        buf->f = src->f;
        if ( buf->s.type == FRAME_BUF )
            hb_buffer_init_planes( buf );
    }

#if HB_PROJECT_FEATURE_QSV
    memcpy(&buf->qsv_details, &src->qsv_details, sizeof(src->qsv_details));
#endif

    return buf;
}