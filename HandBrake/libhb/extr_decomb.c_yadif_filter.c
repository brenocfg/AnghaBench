#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int mode; int cpu_count; TYPE_11__** ref; TYPE_5__* yadif_arguments; int /*<<< orphan*/  yadif_taskset; TYPE_3__** eedi_full; int /*<<< orphan*/  frames; int /*<<< orphan*/  unfiltered; int /*<<< orphan*/  deinterlaced; int /*<<< orphan*/  blended; } ;
typedef  TYPE_6__ hb_filter_private_t ;
struct TYPE_20__ {TYPE_4__* plane; } ;
typedef  TYPE_7__ hb_buffer_t ;
struct TYPE_18__ {int parity; int tff; int mode; TYPE_7__* dst; } ;
struct TYPE_17__ {int width; int height; int stride; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_2__* plane; } ;
struct TYPE_15__ {int stride; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int combed; } ;
struct TYPE_13__ {TYPE_1__ s; } ;

/* Variables and functions */
 size_t DST2PF ; 
 int HB_COMB_HEAVY ; 
 int HB_COMB_LIGHT ; 
 int HB_COMB_NONE ; 
 int MODE_DECOMB_BLEND ; 
 int MODE_DECOMB_EEDI2 ; 
 int MODE_DECOMB_SELECTIVE ; 
 int MODE_DECOMB_YADIF ; 
 int /*<<< orphan*/  eedi2_planer (TYPE_6__*) ; 
 int /*<<< orphan*/  hb_buffer_copy (TYPE_7__*,TYPE_11__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_cycle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void yadif_filter( hb_filter_private_t * pv,
                          hb_buffer_t * dst,
                          int parity,
                          int tff)
{
    /* If we're running comb detection, do it now, otherwise default to true. */
    int is_combed = HB_COMB_HEAVY;
    int mode = 0;

    if (pv->mode & MODE_DECOMB_SELECTIVE)
    {
        is_combed = pv->ref[1]->s.combed;
    }

    // Pick a mode based on the comb detect state and selected decomb modes
    if ((pv->mode & MODE_DECOMB_BLEND) && is_combed == HB_COMB_LIGHT )
    {
        mode = MODE_DECOMB_BLEND;
    }
    else if (is_combed != HB_COMB_NONE)
    {
        mode = pv->mode & ~MODE_DECOMB_SELECTIVE;
    }

    if (mode == MODE_DECOMB_BLEND)
    {
        pv->blended++;
    }
    else if (mode != 0)
    {
        pv->deinterlaced++;
    }
    else
    {
        pv->unfiltered++;
    }
    pv->frames++;

    if (mode & MODE_DECOMB_EEDI2)
    {
        /* Generate an EEDI2 interpolation */
        eedi2_planer( pv );
    }

    if (mode != 0)
    {
        if ((mode & MODE_DECOMB_EEDI2 ) && !(mode & MODE_DECOMB_YADIF))
        {
            // Just pass through the EEDI2 interpolation
            int pp;
            for( pp = 0; pp < 3; pp++ )
            {
                uint8_t * ref = pv->eedi_full[DST2PF]->plane[pp].data;
                int ref_stride = pv->eedi_full[DST2PF]->plane[pp].stride;

                uint8_t * dest = dst->plane[pp].data;
                int width = dst->plane[pp].width;
                int height = dst->plane[pp].height;
                int stride = dst->plane[pp].stride;

                int yy;
                for( yy = 0; yy < height; yy++ )
                {
                    memcpy(dest, ref, width);
                    dest += stride;
                    ref += ref_stride;
                }
            }
        }
        else
        {
            int segment;

            for( segment = 0; segment < pv->cpu_count; segment++ )
            {
                /*
                 * Setup the work for this plane.
                 */
                pv->yadif_arguments[segment].parity = parity;
                pv->yadif_arguments[segment].tff = tff;
                pv->yadif_arguments[segment].dst = dst;
                pv->yadif_arguments[segment].mode = mode;
            }

            /*
             * Allow the taskset threads to make one pass over the data.
             */
            taskset_cycle( &pv->yadif_taskset );

            /*
             * Entire frame is now deinterlaced.
             */
        }
    }
    else
    {
        /*  Just passing through... */
        pv->yadif_arguments[0].mode = mode; // 0
        hb_buffer_copy(dst, pv->ref[1]);
    }
}