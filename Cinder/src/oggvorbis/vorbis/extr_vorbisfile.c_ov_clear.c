#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* close_func ) (scalar_t__) ;} ;
struct TYPE_6__ {int links; scalar_t__ datasource; TYPE_1__ callbacks; int /*<<< orphan*/  oy; scalar_t__ offsets; scalar_t__ serialnos; scalar_t__ pcmlengths; scalar_t__ dataoffsets; scalar_t__ vc; scalar_t__ vi; int /*<<< orphan*/  os; int /*<<< orphan*/  vd; int /*<<< orphan*/  vb; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 int /*<<< orphan*/  _VDBG_dump () ; 
 int /*<<< orphan*/  _ogg_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_sync_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  vorbis_block_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_comment_clear (scalar_t__) ; 
 int /*<<< orphan*/  vorbis_dsp_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_clear (scalar_t__) ; 

int ov_clear(OggVorbis_File *vf){
  if(vf){
    vorbis_block_clear(&vf->vb);
    vorbis_dsp_clear(&vf->vd);
    ogg_stream_clear(&vf->os);

    if(vf->vi && vf->links){
      int i;
      for(i=0;i<vf->links;i++){
        vorbis_info_clear(vf->vi+i);
        vorbis_comment_clear(vf->vc+i);
      }
      _ogg_free(vf->vi);
      _ogg_free(vf->vc);
    }
    if(vf->dataoffsets)_ogg_free(vf->dataoffsets);
    if(vf->pcmlengths)_ogg_free(vf->pcmlengths);
    if(vf->serialnos)_ogg_free(vf->serialnos);
    if(vf->offsets)_ogg_free(vf->offsets);
    ogg_sync_clear(&vf->oy);
    if(vf->datasource && vf->callbacks.close_func)
      (vf->callbacks.close_func)(vf->datasource);
    memset(vf,0,sizeof(*vf));
  }
#ifdef DEBUG_LEAKS
  _VDBG_dump();
#endif
  return(0);
}