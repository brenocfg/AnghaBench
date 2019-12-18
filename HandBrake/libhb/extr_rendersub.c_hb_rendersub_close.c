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
struct TYPE_8__ {int type; int /*<<< orphan*/ * sws; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_9__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

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
 int /*<<< orphan*/  pgssub_close (TYPE_2__*) ; 
 int /*<<< orphan*/  ssa_close (TYPE_2__*) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  textsub_close (TYPE_2__*) ; 
 int /*<<< orphan*/  vobsub_close (TYPE_2__*) ; 

__attribute__((used)) static void hb_rendersub_close( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if (pv->sws != NULL)
    {
        sws_freeContext(pv->sws);
    }
    switch( pv->type )
    {
        case VOBSUB:
        {
            vobsub_close( filter );
        } break;

        case SSASUB:
        {
            ssa_close( filter );
        } break;

        case IMPORTSRT:
        case IMPORTSSA:
        case CC608SUB:
        case UTF8SUB:
        case TX3GSUB:
        {
            textsub_close( filter );
        } break;

        case PGSSUB:
        {
            pgssub_close( filter );
        } break;

        default:
        {
            hb_error("rendersub: unsupported subtitle format %d", pv->type );
        } break;
    }
}