#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ready_state; int /*<<< orphan*/  vb; int /*<<< orphan*/  vd; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 int /*<<< orphan*/  OPENED ; 
 int /*<<< orphan*/  vorbis_block_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_dsp_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _decode_clear(OggVorbis_File *vf){
  vorbis_dsp_clear(&vf->vd);
  vorbis_block_clear(&vf->vb);
  vf->ready_state=OPENED;
}