#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct s_write {int dummy; } ;
struct eia608 {int dummy; } ;
struct TYPE_14__ {TYPE_8__* cc608; TYPE_6__* job; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_15__ {TYPE_7__* subtitle; TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_work_object_t ;
struct TYPE_16__ {int* crop; TYPE_3__* title; } ;
typedef  TYPE_6__ hb_job_t ;
struct TYPE_18__ {int width; int height; int direct_rollup; void* data608; int /*<<< orphan*/  par; int /*<<< orphan*/  crop; } ;
struct TYPE_11__ {scalar_t__ dest; } ;
struct TYPE_17__ {TYPE_1__ config; } ;
struct TYPE_12__ {int width; int height; int /*<<< orphan*/  par; } ;
struct TYPE_13__ {TYPE_2__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_FONT_MONO ; 
 scalar_t__ RENDERSUB ; 
 void* calloc (int,int) ; 
 int general_608_init (TYPE_8__*) ; 
 int /*<<< orphan*/  hb_subtitle_add_ssa_header (TYPE_7__*,int /*<<< orphan*/ ,double,int,int) ; 
 int /*<<< orphan*/  init_eia608 (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int decccInit( hb_work_object_t * w, hb_job_t * job )
{
    int retval = 1;
    hb_work_private_t * pv;

    pv = calloc( 1, sizeof( hb_work_private_t ) );
    if( pv )
    {
        w->private_data = pv;

        pv->job = job;

        pv->cc608 = calloc(1, sizeof(struct s_write));

        if( pv->cc608 )
        {
            pv->cc608->width = job->title->geometry.width;
            pv->cc608->height = job->title->geometry.height;
            memcpy(pv->cc608->crop, job->crop, sizeof(int[4]));
            pv->cc608->par = job->title->geometry.par;
            retval = general_608_init(pv->cc608);
            if( !retval )
            {
                pv->cc608->data608 = calloc(1, sizeof(struct eia608));
                if( !pv->cc608->data608 )
                {
                    retval = 1;
                }
                else
                {
                    init_eia608(pv->cc608->data608);
                }
            }

            // When rendering subs, we need to push rollup subtitles out
            // asap (instead of waiting for a completed line) so that we
            // do not miss the frame that they should be rendered over.
            pv->cc608->direct_rollup = w->subtitle->config.dest == RENDERSUB;
        }

        if (!retval)
        {
            // Generate generic SSA Script Info.
            int height = job->title->geometry.height - job->crop[0] - job->crop[1];
            int width = job->title->geometry.width - job->crop[2] - job->crop[3];
            int safe_height = 0.8 * job->title->geometry.height;
            hb_subtitle_add_ssa_header(w->subtitle, HB_FONT_MONO,
                                       .08 * safe_height, width, height);
        }
    }
    return retval;
}