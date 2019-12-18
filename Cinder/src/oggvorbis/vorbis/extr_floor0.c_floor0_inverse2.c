#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t m; int* n; int /*<<< orphan*/  ln; int /*<<< orphan*/ * linearmap; TYPE_2__* vi; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
typedef  int /*<<< orphan*/  vorbis_look_floor ;
struct TYPE_9__ {scalar_t__ ampdB; } ;
typedef  TYPE_2__ vorbis_info_floor0 ;
struct TYPE_10__ {size_t W; } ;
typedef  TYPE_3__ vorbis_block ;

/* Variables and functions */
 int /*<<< orphan*/  floor0_map_lazy_init (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vorbis_lsp_to_curve (float*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*,size_t,float,float) ; 

__attribute__((used)) static int floor0_inverse2(vorbis_block *vb,vorbis_look_floor *i,
                           void *memo,float *out){
  vorbis_look_floor0 *look=(vorbis_look_floor0 *)i;
  vorbis_info_floor0 *info=look->vi;

  floor0_map_lazy_init(vb,info,look);

  if(memo){
    float *lsp=(float *)memo;
    float amp=lsp[look->m];

    /* take the coefficients back to a spectral envelope curve */
    vorbis_lsp_to_curve(out,
                        look->linearmap[vb->W],
                        look->n[vb->W],
                        look->ln,
                        lsp,look->m,amp,(float)info->ampdB);
    return(1);
  }
  memset(out,0,sizeof(*out)*look->n[vb->W]);
  return(0);
}