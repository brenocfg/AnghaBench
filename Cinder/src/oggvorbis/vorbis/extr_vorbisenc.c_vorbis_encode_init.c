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
typedef  int /*<<< orphan*/  vorbis_info ;

/* Variables and functions */
 int vorbis_encode_setup_init (int /*<<< orphan*/ *) ; 
 int vorbis_encode_setup_managed (int /*<<< orphan*/ *,long,long,long,long,long) ; 
 int /*<<< orphan*/  vorbis_info_clear (int /*<<< orphan*/ *) ; 

int vorbis_encode_init(vorbis_info *vi,
                       long channels,
                       long rate,

                       long max_bitrate,
                       long nominal_bitrate,
                       long min_bitrate){

  int ret=vorbis_encode_setup_managed(vi,channels,rate,
                                      max_bitrate,
                                      nominal_bitrate,
                                      min_bitrate);
  if(ret){
    vorbis_info_clear(vi);
    return(ret);
  }

  ret=vorbis_encode_setup_init(vi);
  if(ret)
    vorbis_info_clear(vi);
  return(ret);
}