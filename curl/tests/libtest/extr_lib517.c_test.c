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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {char* input; scalar_t__ output; } ;

/* Variables and functions */
 scalar_t__ curl_getdate (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* dates ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,scalar_t__) ; 

int test(char *URL)
{
  int i;
  int error = 0;

  (void)URL; /* not used */

  for(i = 0; dates[i].input; i++) {
    time_t out = curl_getdate(dates[i].input, NULL);
    if(out != dates[i].output) {
      printf("WRONGLY %s => %ld (instead of %ld)\n",
             dates[i].input, out, dates[i].output);
      error++;
    }
  }

  return error;
}