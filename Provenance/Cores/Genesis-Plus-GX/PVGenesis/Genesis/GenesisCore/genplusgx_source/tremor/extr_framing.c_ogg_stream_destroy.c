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
struct TYPE_5__ {int /*<<< orphan*/  body_tail; int /*<<< orphan*/  header_tail; } ;
typedef  TYPE_1__ ogg_stream_state ;

/* Variables and functions */
 int OGG_SUCCESS ; 
 int /*<<< orphan*/  _ogg_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_buffer_release (int /*<<< orphan*/ ) ; 

int ogg_stream_destroy(ogg_stream_state *os){
  if(os){
    ogg_buffer_release(os->header_tail);
    ogg_buffer_release(os->body_tail);
    memset(os,0,sizeof(*os));    
    _ogg_free(os);
  }
  return OGG_SUCCESS;
}