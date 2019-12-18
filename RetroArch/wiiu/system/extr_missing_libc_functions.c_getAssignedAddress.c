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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  int /*<<< orphan*/  ACIpAddress ;

/* Variables and functions */
 int ACGetAssignedAddress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int getAssignedAddress(struct sockaddr_in *sa)
{
   ACIpAddress addr;
   int result;
   if (!sa)
      return -1;
   result = ACGetAssignedAddress(&addr);
   if (result == 0)
      sa->sin_addr.s_addr = addr;

   return result;
}