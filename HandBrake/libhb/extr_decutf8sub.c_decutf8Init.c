#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_work_private_t ;
struct TYPE_9__ {int /*<<< orphan*/  subtitle; int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_10__ {int* crop; TYPE_2__* title; } ;
typedef  TYPE_4__ hb_job_t ;
struct TYPE_7__ {int height; int width; } ;
struct TYPE_8__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_FONT_SANS ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  hb_subtitle_add_ssa_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int,int) ; 

__attribute__((used)) static int decutf8Init(hb_work_object_t *w, hb_job_t *job)
{
    hb_work_private_t * pv;
    pv = calloc( 1, sizeof( hb_work_private_t ) );
    if (pv == NULL)
        return 1;
    w->private_data = pv;

    // Generate generic SSA Script Info.
    int height = job->title->geometry.height - job->crop[0] - job->crop[1];
    int width = job->title->geometry.width - job->crop[2] - job->crop[3];
    hb_subtitle_add_ssa_header(w->subtitle, HB_FONT_SANS,
                               .066 * job->title->geometry.height,
                               width, height);

    return 0;
}