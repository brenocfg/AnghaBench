#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_9__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
#define  CC608SUB 135 
#define  IMPORTSRT 134 
#define  IMPORTSSA 133 
#define  PGSSUB 132 
#define  SSASUB 131 
#define  TX3GSUB 130 
#define  UTF8SUB 129 
#define  VOBSUB 128 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 int pgssub_work (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int ssa_work (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int textsub_work (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int vobsub_work (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int hb_rendersub_work( hb_filter_object_t * filter,
                                 hb_buffer_t ** buf_in,
                                 hb_buffer_t ** buf_out )
{
    hb_filter_private_t * pv = filter->private_data;
    switch( pv->type )
    {
        case VOBSUB:
        {
            return vobsub_work( filter, buf_in, buf_out );
        } break;

        case SSASUB:
        {
            return ssa_work( filter, buf_in, buf_out );
        } break;

        case IMPORTSRT:
        case IMPORTSSA:
        case CC608SUB:
        case UTF8SUB:
        case TX3GSUB:
        {
            return textsub_work( filter, buf_in, buf_out );
        } break;

        case PGSSUB:
        {
            return pgssub_work( filter, buf_in, buf_out );
        } break;

        default:
        {
            hb_error("rendersub: unsupported subtitle format %d", pv->type );
            return 1;
        } break;
    }
}