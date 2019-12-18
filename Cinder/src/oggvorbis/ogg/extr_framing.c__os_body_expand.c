#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long body_storage; long body_fill; void* body_data; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 long LONG_MAX ; 
 void* _ogg_realloc (void*,long) ; 
 int /*<<< orphan*/  ogg_stream_clear (TYPE_1__*) ; 

__attribute__((used)) static int _os_body_expand(ogg_stream_state *os,long needed){
  if(os->body_storage-needed<=os->body_fill){
    long body_storage;
    void *ret;
    if(os->body_storage>LONG_MAX-needed){
      ogg_stream_clear(os);
      return -1;
    }
    body_storage=os->body_storage+needed;
    if(body_storage<LONG_MAX-1024)body_storage+=1024;
    ret=_ogg_realloc(os->body_data,body_storage*sizeof(*os->body_data));
    if(!ret){
      ogg_stream_clear(os);
      return -1;
    }
    os->body_storage=body_storage;
    os->body_data=ret;
  }
  return 0;
}