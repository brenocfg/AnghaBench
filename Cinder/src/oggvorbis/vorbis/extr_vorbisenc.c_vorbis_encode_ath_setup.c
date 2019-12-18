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
struct TYPE_7__ {int /*<<< orphan*/  ath_maxatt; int /*<<< orphan*/  ath_adjatt; } ;
typedef  TYPE_2__ vorbis_info_psy ;
struct TYPE_8__ {TYPE_4__* codec_setup; } ;
typedef  TYPE_3__ vorbis_info ;
struct TYPE_6__ {int /*<<< orphan*/  ath_absolute_dB; int /*<<< orphan*/  ath_floating_dB; } ;
struct TYPE_9__ {TYPE_1__ hi; TYPE_2__** psy_param; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */

__attribute__((used)) static void vorbis_encode_ath_setup(vorbis_info *vi,int block){
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy *p=ci->psy_param[block];

  p->ath_adjatt=ci->hi.ath_floating_dB;
  p->ath_maxatt=ci->hi.ath_absolute_dB;
  return;
}