#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_int64_t ;
typedef  int /*<<< orphan*/  OggVorbis_File ;

/* Variables and functions */
 int _ov_64_seek_lap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_pcm_seek_page ; 

int ov_pcm_seek_page_lap(OggVorbis_File *vf,ogg_int64_t pos){
  return _ov_64_seek_lap(vf,pos,ov_pcm_seek_page);
}