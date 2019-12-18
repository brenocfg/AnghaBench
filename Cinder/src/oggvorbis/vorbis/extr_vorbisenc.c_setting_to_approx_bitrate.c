#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int channels; TYPE_4__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_7__ {double* rate_mapping; } ;
typedef  TYPE_2__ ve_setup_data_template ;
struct TYPE_8__ {int base_setting; scalar_t__ setup; } ;
typedef  TYPE_3__ highlevel_encode_setup ;
struct TYPE_9__ {TYPE_3__ hi; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */

__attribute__((used)) static double setting_to_approx_bitrate(vorbis_info *vi){
  codec_setup_info *ci=vi->codec_setup;
  highlevel_encode_setup *hi=&ci->hi;
  ve_setup_data_template *setup=(ve_setup_data_template *)hi->setup;
  int is=hi->base_setting;
  double ds=hi->base_setting-is;
  int ch=vi->channels;
  const double *r=setup->rate_mapping;

  if(r==NULL)
    return(-1);

  return((r[is]*(1.-ds)+r[is+1]*ds)*ch);
}