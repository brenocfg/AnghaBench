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
struct TYPE_4__ {int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ GlobalInfo ;

/* Variables and functions */
 long EOF ; 
 long fscanf (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  new_conn (char*,TYPE_1__*) ; 

__attribute__((used)) static void fifo_cb(GlobalInfo* g, int revents)
{
  char s[1024];
  long int rv = 0;
  int n = 0;

  do {
    s[0]='\0';
    rv = fscanf(g->input, "%1023s%n", s, &n);
    s[n]='\0';
    if(n && s[0]) {
      new_conn(s, g); /* if we read a URL, go get it! */
    }
    else
      break;
  } while(rv != EOF);
}