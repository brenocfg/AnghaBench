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
typedef  int /*<<< orphan*/  ogg_int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* seek_func ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  oy; int /*<<< orphan*/  offset; scalar_t__ datasource; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ogg_sync_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _seek_helper(OggVorbis_File *vf,ogg_int64_t offset){
  if(vf->datasource){
    (vf->callbacks.seek_func)(vf->datasource, offset, SEEK_SET);
    vf->offset=offset;
    ogg_sync_reset(vf->oy);
  }else{
    /* shouldn't happen unless someone writes a broken callback */
    return;
  }
}