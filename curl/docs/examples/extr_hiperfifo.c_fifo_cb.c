#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int stopped; scalar_t__ still_running; int /*<<< orphan*/  evbase; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ GlobalInfo ;

/* Variables and functions */
 long EOF ; 
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 
 long fscanf (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  new_conn (char*,void*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void fifo_cb(int fd, short event, void *arg)
{
  char s[1024];
  long int rv = 0;
  int n = 0;
  GlobalInfo *g = (GlobalInfo *)arg;
  (void)fd;
  (void)event;

  do {
    s[0]='\0';
    rv = fscanf(g->input, "%1023s%n", s, &n);
    s[n]='\0';
    if(n && s[0]) {
      if(!strcmp(s, "stop")) {
        g->stopped = 1;
        if(g->still_running == 0)
          event_base_loopbreak(g->evbase);
      }
      else
        new_conn(s, arg);  /* if we read a URL, go get it! */
    }
    else
      break;
  } while(rv != EOF);
}