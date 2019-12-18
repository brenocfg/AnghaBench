#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int channels; int rate; int bitrate_upper; int bitrate_nominal; int bitrate_lower; TYPE_2__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_5__ {int /*<<< orphan*/ * blocksizes; } ;
typedef  TYPE_2__ codec_setup_info ;

/* Variables and functions */
 int OV_EFAULT ; 
 int /*<<< orphan*/  _v_writestring (int /*<<< orphan*/ *,char*,int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int _vorbis_pack_info(oggpack_buffer *opb,vorbis_info *vi){
  codec_setup_info     *ci=vi->codec_setup;
  if(!ci)return(OV_EFAULT);

  /* preamble */
  oggpack_write(opb,0x01,8);
  _v_writestring(opb,"vorbis", 6);

  /* basic information about the stream */
  oggpack_write(opb,0x00,32);
  oggpack_write(opb,vi->channels,8);
  oggpack_write(opb,vi->rate,32);

  oggpack_write(opb,vi->bitrate_upper,32);
  oggpack_write(opb,vi->bitrate_nominal,32);
  oggpack_write(opb,vi->bitrate_lower,32);

  oggpack_write(opb,ilog2(ci->blocksizes[0]),4);
  oggpack_write(opb,ilog2(ci->blocksizes[1]),4);
  oggpack_write(opb,1,1);

  return(0);
}