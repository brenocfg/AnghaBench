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
struct Curl_multi {int recheckstate; } ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static bool multi_ischanged(struct Curl_multi *multi, bool clear)
{
  bool retval = multi->recheckstate;
  if(clear)
    multi->recheckstate = FALSE;
  return retval;
}