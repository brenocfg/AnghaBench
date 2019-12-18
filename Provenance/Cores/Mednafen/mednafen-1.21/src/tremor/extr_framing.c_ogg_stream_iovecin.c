#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* lacing_vals; int lacing_fill; int e_o_s; int /*<<< orphan*/  packetno; int /*<<< orphan*/ * granule_vals; int /*<<< orphan*/  granulepos; scalar_t__ body_fill; scalar_t__ body_data; scalar_t__ body_returned; } ;
typedef  TYPE_1__ ogg_stream_state ;
struct TYPE_9__ {long iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  TYPE_2__ ogg_iovec_t ;
typedef  int /*<<< orphan*/  ogg_int64_t ;

/* Variables and functions */
 long LONG_MAX ; 
 scalar_t__ _os_body_expand (TYPE_1__*,long) ; 
 scalar_t__ _os_lacing_expand (TYPE_1__*,long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ogg_stream_check (TYPE_1__*) ; 

int ogg_stream_iovecin(ogg_stream_state *os, ogg_iovec_t *iov, int count,
                       long e_o_s, ogg_int64_t granulepos){

  long bytes = 0, lacing_vals;
  int i;

  if(ogg_stream_check(os)) return -1;
  if(!iov) return 0;

  for (i = 0; i < count; ++i){
    if(iov[i].iov_len>LONG_MAX) return -1;
    if(bytes>LONG_MAX-(long)iov[i].iov_len) return -1;
    bytes += (long)iov[i].iov_len;
  }
  lacing_vals=bytes/255+1;

  if(os->body_returned){
    /* advance packet data according to the body_returned pointer. We
       had to keep it around to return a pointer into the buffer last
       call */

    os->body_fill-=os->body_returned;
    if(os->body_fill)
      memmove(os->body_data,os->body_data+os->body_returned,
              os->body_fill);
    os->body_returned=0;
  }

  /* make sure we have the buffer storage */
  if(_os_body_expand(os,bytes) || _os_lacing_expand(os,lacing_vals))
    return -1;

  /* Copy in the submitted packet.  Yes, the copy is a waste; this is
     the liability of overly clean abstraction for the time being.  It
     will actually be fairly easy to eliminate the extra copy in the
     future */

  for (i = 0; i < count; ++i) {
    memcpy(os->body_data+os->body_fill, iov[i].iov_base, iov[i].iov_len);
    os->body_fill += (int)iov[i].iov_len;
  }

  /* Store lacing vals for this packet */
  for(i=0;i<lacing_vals-1;i++){
    os->lacing_vals[os->lacing_fill+i]=255;
    os->granule_vals[os->lacing_fill+i]=os->granulepos;
  }
  os->lacing_vals[os->lacing_fill+i]=bytes%255;
  os->granulepos=os->granule_vals[os->lacing_fill+i]=granulepos;

  /* flag the first segment as the beginning of the packet */
  os->lacing_vals[os->lacing_fill]|= 0x100;

  os->lacing_fill+=lacing_vals;

  /* for the sake of completeness */
  os->packetno++;

  if(e_o_s)os->e_o_s=1;

  return(0);
}