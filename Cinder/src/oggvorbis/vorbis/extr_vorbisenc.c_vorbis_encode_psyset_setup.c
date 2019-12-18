#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int blockflag; int normal_p; int normal_start; int normal_partition; double normal_thresh; } ;
typedef  TYPE_1__ vorbis_info_psy ;
struct TYPE_9__ {TYPE_4__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_10__ {scalar_t__ noise_normalize_p; } ;
typedef  TYPE_3__ highlevel_encode_setup ;
struct TYPE_11__ {int psys; TYPE_1__** psy_param; TYPE_3__ hi; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */
 TYPE_1__* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  _psy_info_template ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vorbis_encode_psyset_setup(vorbis_info *vi,double s,
                                       const int *nn_start,
                                       const int *nn_partition,
                                       const double *nn_thresh,
                                       int block){
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy *p=ci->psy_param[block];
  highlevel_encode_setup *hi=&ci->hi;
  int is=s;

  if(block>=ci->psys)
    ci->psys=block+1;
  if(!p){
    p=_ogg_calloc(1,sizeof(*p));
    ci->psy_param[block]=p;
  }

  memcpy(p,&_psy_info_template,sizeof(*p));
  p->blockflag=block>>1;

  if(hi->noise_normalize_p){
    p->normal_p=1;
    p->normal_start=nn_start[is];
    p->normal_partition=nn_partition[is];
    p->normal_thresh=nn_thresh[is];
  }

  return;
}