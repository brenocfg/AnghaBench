#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_7__ {float req; int coupling_p; scalar_t__ managed; int /*<<< orphan*/  setup; int /*<<< orphan*/  base_setting; } ;
typedef  TYPE_2__ highlevel_encode_setup ;
struct TYPE_8__ {TYPE_2__ hi; } ;
typedef  TYPE_3__ codec_setup_info ;

/* Variables and functions */
 int OV_EIMPL ; 
 int /*<<< orphan*/  get_setup_template (long,long,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_encode_setup_setting (TYPE_1__*,long,long) ; 

int vorbis_encode_setup_vbr(vorbis_info *vi,
                            long  channels,
                            long  rate,
                            float quality){
  codec_setup_info *ci=vi->codec_setup;
  highlevel_encode_setup *hi=&ci->hi;

  quality+=.0000001;
  if(quality>=1.)quality=.9999;

  hi->req=quality;
  hi->setup=get_setup_template(channels,rate,quality,0,&hi->base_setting);
  if(!hi->setup)return OV_EIMPL;

  vorbis_encode_setup_setting(vi,channels,rate);
  hi->managed=0;
  hi->coupling_p=1;

  return 0;
}