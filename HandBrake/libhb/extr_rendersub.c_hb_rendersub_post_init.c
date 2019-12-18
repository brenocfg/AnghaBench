#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * crop; } ;
typedef  TYPE_1__ hb_job_t ;
struct TYPE_17__ {int type; int /*<<< orphan*/ * crop; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_18__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;

/* Variables and functions */
#define  CC608SUB 135 
#define  IMPORTSRT 134 
#define  IMPORTSSA 133 
#define  PGSSUB 132 
#define  SSASUB 131 
#define  TX3GSUB 130 
#define  UTF8SUB 129 
#define  VOBSUB 128 
 int cc608sub_post_init (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 
 int pgssub_post_init (TYPE_3__*,TYPE_1__*) ; 
 int ssa_post_init (TYPE_3__*,TYPE_1__*) ; 
 int textsub_post_init (TYPE_3__*,TYPE_1__*) ; 
 int vobsub_post_init (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int hb_rendersub_post_init( hb_filter_object_t * filter, hb_job_t *job )
{
    hb_filter_private_t * pv = filter->private_data;

    pv->crop[0] = job->crop[0];
    pv->crop[1] = job->crop[1];
    pv->crop[2] = job->crop[2];
    pv->crop[3] = job->crop[3];

    switch( pv->type )
    {
        case VOBSUB:
        {
            return vobsub_post_init( filter, job );
        } break;

        case SSASUB:
        {
            return ssa_post_init( filter, job );
        } break;

        case IMPORTSRT:
        case IMPORTSSA:
        case UTF8SUB:
        case TX3GSUB:
        {
            return textsub_post_init( filter, job );
        } break;

        case CC608SUB:
        {
            return cc608sub_post_init( filter, job );
        } break;

        case PGSSUB:
        {
            return pgssub_post_init( filter, job );
        } break;

        default:
        {
            hb_log("rendersub: unsupported subtitle format %d", pv->type );
            return 1;
        } break;
    }
    return 0;
}