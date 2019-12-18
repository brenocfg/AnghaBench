#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* context; int /*<<< orphan*/  file; TYPE_1__* job; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_9__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_10__ {char* stats_out; } ;
struct TYPE_7__ {scalar_t__ pass_id; } ;

/* Variables and functions */
 scalar_t__ HB_PASS_ENCODE_1ST ; 
 int /*<<< orphan*/  avcodec_send_frame (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_packets (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Flush( hb_work_object_t * w, hb_buffer_list_t * list )
{
    hb_work_private_t * pv = w->private_data;

    avcodec_send_frame(pv->context, NULL);

    // Write stats
    // vpx only writes stats at final flush
    if (pv->job->pass_id == HB_PASS_ENCODE_1ST &&
        pv->context->stats_out != NULL)
    {
        fprintf( pv->file, "%s", pv->context->stats_out );
    }

    get_packets(w, list);
}