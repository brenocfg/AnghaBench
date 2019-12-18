#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ready_state; int /*<<< orphan*/ * datasource; scalar_t__ seekable; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int _open_seekable2 (TYPE_1__*) ; 
 int /*<<< orphan*/  ov_clear (TYPE_1__*) ; 

__attribute__((used)) static int _ov_open2(OggVorbis_File *vf){
  if(vf->ready_state < OPENED)
    vf->ready_state=OPENED;
  if(vf->seekable){
    int ret=_open_seekable2(vf);
    if(ret){
      vf->datasource=NULL;
      ov_clear(vf);
    }
    return(ret);
  }
  return 0;
}