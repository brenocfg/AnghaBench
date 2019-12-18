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
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_4__ {int (* seek_func ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ offset; int /*<<< orphan*/  oy; scalar_t__ datasource; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 int OV_EFAULT ; 
 int OV_EREAD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ogg_sync_reset (int /*<<< orphan*/ *) ; 
 int stub1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _seek_helper(OggVorbis_File *vf,ogg_int64_t offset){
  if(vf->datasource){
    /* only seek if the file position isn't already there */
    if(vf->offset != offset){
      if(!(vf->callbacks.seek_func)||
         (vf->callbacks.seek_func)(vf->datasource, offset, SEEK_SET) == -1)
        return OV_EREAD;
      vf->offset=offset;
      ogg_sync_reset(&vf->oy);
    }
  }else{
    /* shouldn't happen unless someone writes a broken callback */
    return OV_EFAULT;
  }
  return 0;
}