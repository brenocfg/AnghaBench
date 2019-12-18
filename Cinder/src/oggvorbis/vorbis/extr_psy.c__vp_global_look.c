#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ampmax; int /*<<< orphan*/ * gi; int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ vorbis_look_psy_global ;
typedef  int /*<<< orphan*/  vorbis_info_psy_global ;
struct TYPE_8__ {int /*<<< orphan*/  channels; TYPE_3__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_9__ {int /*<<< orphan*/  psy_g_param; } ;
typedef  TYPE_3__ codec_setup_info ;

/* Variables and functions */
 TYPE_1__* _ogg_calloc (int,int) ; 

vorbis_look_psy_global *_vp_global_look(vorbis_info *vi){
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *gi=&ci->psy_g_param;
  vorbis_look_psy_global *look=_ogg_calloc(1,sizeof(*look));

  look->channels=vi->channels;

  look->ampmax=-9999.;
  look->gi=gi;
  return(look);
}