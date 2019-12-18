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
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vorbis_look_residue ;
struct TYPE_15__ {int /*<<< orphan*/  ch; TYPE_5__** residue_func; int /*<<< orphan*/ ** residue_look; TYPE_6__** floor_func; int /*<<< orphan*/ ** floor_look; int /*<<< orphan*/ * mode; TYPE_3__* map; } ;
typedef  TYPE_1__ vorbis_look_mapping0 ;
typedef  TYPE_1__ vorbis_look_mapping ;
typedef  int /*<<< orphan*/  vorbis_look_floor ;
typedef  int /*<<< orphan*/  vorbis_info_mode ;
struct TYPE_16__ {int submaps; int* floorsubmap; int* residuesubmap; } ;
typedef  TYPE_3__ vorbis_info_mapping0 ;
typedef  int /*<<< orphan*/  vorbis_info_mapping ;
struct TYPE_17__ {int /*<<< orphan*/  channels; scalar_t__ codec_setup; } ;
typedef  TYPE_4__ vorbis_info ;
struct TYPE_18__ {int /*<<< orphan*/ * (* look ) (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ vorbis_func_residue ;
struct TYPE_19__ {int /*<<< orphan*/ * (* look ) (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__ vorbis_func_floor ;
struct TYPE_20__ {TYPE_4__* vi; } ;
typedef  TYPE_7__ vorbis_dsp_state ;
struct TYPE_21__ {size_t* floor_type; size_t* residue_type; int /*<<< orphan*/ * residue_param; int /*<<< orphan*/ * floor_param; } ;
typedef  TYPE_8__ codec_setup_info ;

/* Variables and functions */
 TYPE_6__** _floor_P ; 
 scalar_t__ _ogg_calloc (int,int) ; 
 TYPE_5__** _residue_P ; 
 int /*<<< orphan*/ * stub1 (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vorbis_look_mapping *mapping0_look(vorbis_dsp_state *vd,vorbis_info_mode *vm,
			  vorbis_info_mapping *m){
  int i;
  vorbis_info          *vi=vd->vi;
  codec_setup_info     *ci=(codec_setup_info *)vi->codec_setup;
  vorbis_look_mapping0 *look=(vorbis_look_mapping0 *)_ogg_calloc(1,sizeof(*look));
  vorbis_info_mapping0 *info=look->map=(vorbis_info_mapping0 *)m;
  look->mode=vm;
  
  look->floor_look=(vorbis_look_floor **)_ogg_calloc(info->submaps,sizeof(*look->floor_look));

  look->residue_look=(vorbis_look_residue **)_ogg_calloc(info->submaps,sizeof(*look->residue_look));

  look->floor_func=(vorbis_func_floor **)_ogg_calloc(info->submaps,sizeof(*look->floor_func));
  look->residue_func=(vorbis_func_residue **)_ogg_calloc(info->submaps,sizeof(*look->residue_func));
  
  for(i=0;i<info->submaps;i++){
    int floornum=info->floorsubmap[i];
    int resnum=info->residuesubmap[i];

    look->floor_func[i]=_floor_P[ci->floor_type[floornum]];
    look->floor_look[i]=look->floor_func[i]->
      look(vd,vm,ci->floor_param[floornum]);
    look->residue_func[i]=_residue_P[ci->residue_type[resnum]];
    look->residue_look[i]=look->residue_func[i]->
      look(vd,vm,ci->residue_param[resnum]);
    
  }

  look->ch=vi->channels;

  return(look);
}