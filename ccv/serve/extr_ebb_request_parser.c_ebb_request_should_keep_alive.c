#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int keep_alive; int version_major; scalar_t__ version_minor; } ;
typedef  TYPE_1__ ebb_request ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

int ebb_request_should_keep_alive(ebb_request *request)
{
  if(request->keep_alive == -1)
    if(request->version_major == 1)
      return (request->version_minor != 0);
    else if(request->version_major == 0)
      return FALSE;
    else
      return TRUE;
  else
    return request->keep_alive;
}