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
typedef  int /*<<< orphan*/  OggVorbis_File ;

/* Variables and functions */
 int _ov_d_seek_lap (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_time_seek_page ; 

int ov_time_seek_page_lap(OggVorbis_File *vf,double pos){
  return _ov_d_seek_lap(vf,pos,ov_time_seek_page);
}