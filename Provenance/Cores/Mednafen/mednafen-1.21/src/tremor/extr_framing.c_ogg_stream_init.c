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
struct TYPE_5__ {int body_storage; int lacing_storage; int serialno; void* granule_vals; void* lacing_vals; void* body_data; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 void* _ogg_malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_stream_clear (TYPE_1__*) ; 

int ogg_stream_init(ogg_stream_state *os,int serialno){
  if(os){
    memset(os,0,sizeof(*os));
    os->body_storage=16*1024;
    os->lacing_storage=1024;

    os->body_data=_ogg_malloc(os->body_storage*sizeof(*os->body_data));
    os->lacing_vals=_ogg_malloc(os->lacing_storage*sizeof(*os->lacing_vals));
    os->granule_vals=_ogg_malloc(os->lacing_storage*sizeof(*os->granule_vals));

    if(!os->body_data || !os->lacing_vals || !os->granule_vals){
      ogg_stream_clear(os);
      return -1;
    }

    os->serialno=serialno;

    return(0);
  }
  return(-1);
}