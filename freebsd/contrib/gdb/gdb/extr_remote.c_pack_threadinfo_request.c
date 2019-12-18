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
typedef  int /*<<< orphan*/  threadref ;

/* Variables and functions */
 char* pack_int (char*,int) ; 
 char* pack_threadid (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
pack_threadinfo_request (char *pkt, int mode, threadref *id)
{
  *pkt++ = 'q';			/* Info Query */
  *pkt++ = 'P';			/* process or thread info */
  pkt = pack_int (pkt, mode);	/* mode */
  pkt = pack_threadid (pkt, id);	/* threadid */
  *pkt = '\0';			/* terminate */
  return pkt;
}