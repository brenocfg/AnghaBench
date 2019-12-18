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
struct TYPE_5__ {int unsynced; } ;
typedef  TYPE_1__ ogg_sync_state ;
typedef  int /*<<< orphan*/  ogg_page ;

/* Variables and functions */
 scalar_t__ ogg_sync_check (TYPE_1__*) ; 
 long ogg_sync_pageseek (TYPE_1__*,int /*<<< orphan*/ *) ; 

int ogg_sync_pageout(ogg_sync_state *oy, ogg_page *og){

  if(ogg_sync_check(oy))return 0;

  /* all we need to do is verify a page at the head of the stream
     buffer.  If it doesn't verify, we look for the next potential
     frame */

  for(;;){
    long ret=ogg_sync_pageseek(oy,og);
    if(ret>0){
      /* have a page */
      return(1);
    }
    if(ret==0){
      /* need more data */
      return(0);
    }

    /* head did not start a synced page... skipped some bytes */
    if(!oy->unsynced){
      oy->unsynced=1;
      return(-1);
    }

    /* loop. keep looking */

  }
}