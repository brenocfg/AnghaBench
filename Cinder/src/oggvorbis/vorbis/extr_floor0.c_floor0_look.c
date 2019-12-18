#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* linearmap; TYPE_3__* vi; int /*<<< orphan*/  ln; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
typedef  TYPE_1__ vorbis_look_floor ;
struct TYPE_6__ {int /*<<< orphan*/  barkmap; int /*<<< orphan*/  order; } ;
typedef  TYPE_3__ vorbis_info_floor0 ;
typedef  int /*<<< orphan*/  vorbis_info_floor ;
typedef  int /*<<< orphan*/  vorbis_dsp_state ;

/* Variables and functions */
 void* _ogg_calloc (int,int) ; 

__attribute__((used)) static vorbis_look_floor *floor0_look(vorbis_dsp_state *vd,
                                      vorbis_info_floor *i){
  vorbis_info_floor0 *info=(vorbis_info_floor0 *)i;
  vorbis_look_floor0 *look=_ogg_calloc(1,sizeof(*look));

  (void)vd;

  look->m=info->order;
  look->ln=info->barkmap;
  look->vi=info;

  look->linearmap=_ogg_calloc(2,sizeof(*look->linearmap));

  return look;
}