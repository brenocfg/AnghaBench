#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_15__ {int books; int floors; int* floor_type; int residues; int* residue_type; int maps; int* map_type; int modes; TYPE_9__** mode_param; int /*<<< orphan*/ * map_param; int /*<<< orphan*/ * residue_param; int /*<<< orphan*/ * floor_param; int /*<<< orphan*/ * book_param; } ;
typedef  TYPE_2__ codec_setup_info ;
struct TYPE_17__ {int blockflag; int windowtype; int transformtype; int mapping; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* unpack ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* unpack ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* unpack ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int OV_EBADHEADER ; 
 int OV_EFAULT ; 
 int VI_FLOORB ; 
 int VI_MAPB ; 
 int VI_RESB ; 
 int VI_TIMEB ; 
 int VI_WINDOWB ; 
 TYPE_11__** _floor_P ; 
 TYPE_10__** _mapping_P ; 
 TYPE_9__* _ogg_calloc (int,int) ; 
 TYPE_8__** _residue_P ; 
 int oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_staticbook_unpack (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _vorbis_unpack_books(vorbis_info *vi,oggpack_buffer *opb){
  codec_setup_info     *ci=vi->codec_setup;
  int i;
  if(!ci)return(OV_EFAULT);

  /* codebooks */
  ci->books=oggpack_read(opb,8)+1;
  if(ci->books<=0)goto err_out;
  for(i=0;i<ci->books;i++){
    ci->book_param[i]=vorbis_staticbook_unpack(opb);
    if(!ci->book_param[i])goto err_out;
  }

  /* time backend settings; hooks are unused */
  {
    int times=oggpack_read(opb,6)+1;
    if(times<=0)goto err_out;
    for(i=0;i<times;i++){
      int test=oggpack_read(opb,16);
      if(test<0 || test>=VI_TIMEB)goto err_out;
    }
  }

  /* floor backend settings */
  ci->floors=oggpack_read(opb,6)+1;
  if(ci->floors<=0)goto err_out;
  for(i=0;i<ci->floors;i++){
    ci->floor_type[i]=oggpack_read(opb,16);
    if(ci->floor_type[i]<0 || ci->floor_type[i]>=VI_FLOORB)goto err_out;
    ci->floor_param[i]=_floor_P[ci->floor_type[i]]->unpack(vi,opb);
    if(!ci->floor_param[i])goto err_out;
  }

  /* residue backend settings */
  ci->residues=oggpack_read(opb,6)+1;
  if(ci->residues<=0)goto err_out;
  for(i=0;i<ci->residues;i++){
    ci->residue_type[i]=oggpack_read(opb,16);
    if(ci->residue_type[i]<0 || ci->residue_type[i]>=VI_RESB)goto err_out;
    ci->residue_param[i]=_residue_P[ci->residue_type[i]]->unpack(vi,opb);
    if(!ci->residue_param[i])goto err_out;
  }

  /* map backend settings */
  ci->maps=oggpack_read(opb,6)+1;
  if(ci->maps<=0)goto err_out;
  for(i=0;i<ci->maps;i++){
    ci->map_type[i]=oggpack_read(opb,16);
    if(ci->map_type[i]<0 || ci->map_type[i]>=VI_MAPB)goto err_out;
    ci->map_param[i]=_mapping_P[ci->map_type[i]]->unpack(vi,opb);
    if(!ci->map_param[i])goto err_out;
  }

  /* mode settings */
  ci->modes=oggpack_read(opb,6)+1;
  if(ci->modes<=0)goto err_out;
  for(i=0;i<ci->modes;i++){
    ci->mode_param[i]=_ogg_calloc(1,sizeof(*ci->mode_param[i]));
    ci->mode_param[i]->blockflag=oggpack_read(opb,1);
    ci->mode_param[i]->windowtype=oggpack_read(opb,16);
    ci->mode_param[i]->transformtype=oggpack_read(opb,16);
    ci->mode_param[i]->mapping=oggpack_read(opb,8);

    if(ci->mode_param[i]->windowtype>=VI_WINDOWB)goto err_out;
    if(ci->mode_param[i]->transformtype>=VI_WINDOWB)goto err_out;
    if(ci->mode_param[i]->mapping>=ci->maps)goto err_out;
    if(ci->mode_param[i]->mapping<0)goto err_out;
  }

  if(oggpack_read(opb,1)!=1)goto err_out; /* top level EOP check */

  return(0);
 err_out:
  vorbis_info_clear(vi);
  return(OV_EBADHEADER);
}