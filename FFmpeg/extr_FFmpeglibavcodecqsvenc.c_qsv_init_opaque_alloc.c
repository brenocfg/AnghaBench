#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  Info; } ;
typedef  TYPE_5__ mfxFrameSurface1 ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_21__ {TYPE_7__* hwaccel_context; } ;
struct TYPE_20__ {int nb_opaque_surfaces; int /*<<< orphan*/  opaque_alloc_type; TYPE_12__* opaque_surfaces; } ;
struct TYPE_17__ {int NumFrameSuggested; int /*<<< orphan*/  Type; int /*<<< orphan*/  Info; } ;
struct TYPE_15__ {int NumSurface; int /*<<< orphan*/  Type; TYPE_5__** Surfaces; } ;
struct TYPE_14__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_16__ {TYPE_2__ In; TYPE_1__ Header; } ;
struct TYPE_19__ {TYPE_4__ req; TYPE_12__* opaque_alloc_buf; TYPE_3__ opaque_alloc; int /*<<< orphan*/  nb_extparam_internal; int /*<<< orphan*/ ** extparam_internal; TYPE_5__** opaque_surfaces; } ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  TYPE_6__ QSVEncContext ;
typedef  TYPE_7__ AVQSVContext ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION ; 
 TYPE_12__* av_buffer_allocz (int) ; 
 TYPE_5__** av_malloc_array (int,int) ; 

__attribute__((used)) static int qsv_init_opaque_alloc(AVCodecContext *avctx, QSVEncContext *q)
{
    AVQSVContext *qsv = avctx->hwaccel_context;
    mfxFrameSurface1 *surfaces;
    int nb_surfaces, i;

    nb_surfaces = qsv->nb_opaque_surfaces + q->req.NumFrameSuggested;

    q->opaque_alloc_buf = av_buffer_allocz(sizeof(*surfaces) * nb_surfaces);
    if (!q->opaque_alloc_buf)
        return AVERROR(ENOMEM);

    q->opaque_surfaces = av_malloc_array(nb_surfaces, sizeof(*q->opaque_surfaces));
    if (!q->opaque_surfaces)
        return AVERROR(ENOMEM);

    surfaces = (mfxFrameSurface1*)q->opaque_alloc_buf->data;
    for (i = 0; i < nb_surfaces; i++) {
        surfaces[i].Info      = q->req.Info;
        q->opaque_surfaces[i] = surfaces + i;
    }

    q->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
    q->opaque_alloc.Header.BufferSz = sizeof(q->opaque_alloc);
    q->opaque_alloc.In.Surfaces     = q->opaque_surfaces;
    q->opaque_alloc.In.NumSurface   = nb_surfaces;
    q->opaque_alloc.In.Type         = q->req.Type;

    q->extparam_internal[q->nb_extparam_internal++] = (mfxExtBuffer *)&q->opaque_alloc;

    qsv->nb_opaque_surfaces = nb_surfaces;
    qsv->opaque_surfaces    = q->opaque_alloc_buf;
    qsv->opaque_alloc_type  = q->req.Type;

    return 0;
}