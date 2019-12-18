#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t m; int n; int /*<<< orphan*/  lsp_look; int /*<<< orphan*/  ln; int /*<<< orphan*/  linearmap; TYPE_2__* vi; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
typedef  int /*<<< orphan*/  vorbis_look_floor ;
struct TYPE_4__ {int /*<<< orphan*/  ampdB; } ;
typedef  TYPE_2__ vorbis_info_floor0 ;
typedef  int /*<<< orphan*/  vorbis_block ;
typedef  int /*<<< orphan*/  ogg_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vorbis_lsp_to_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int floor0_inverse2(vorbis_block *vb,vorbis_look_floor *i,
			   void *memo,ogg_int32_t *out){
  vorbis_look_floor0 *look=(vorbis_look_floor0 *)i;
  vorbis_info_floor0 *info=look->vi;
  
  if(memo){
    ogg_int32_t *lsp=(ogg_int32_t *)memo;
    ogg_int32_t amp=lsp[look->m];

    /* take the coefficients back to a spectral envelope curve */
    vorbis_lsp_to_curve(out,look->linearmap,look->n,look->ln,
			lsp,look->m,amp,info->ampdB,look->lsp_look);
    return(1);
  }
  memset(out,0,sizeof(*out)*look->n);
  return(0);
}