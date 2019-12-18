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
struct TYPE_4__ {int mainver; int minor; } ;
typedef  scalar_t__ Result ;
typedef  TYPE_1__ OS_VersionBin ;

/* Variables and functions */
 scalar_t__ osGetSystemVersionData (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void frontend_ctr_get_os(char* s, size_t len, int* major, int* minor)
{
   OS_VersionBin cver;
   OS_VersionBin nver;

   strlcpy(s, "3DS OS", len);
   Result data_invalid = osGetSystemVersionData(&nver, &cver);
   if (data_invalid == 0)
   {
      *major = cver.mainver;
      *minor = cver.minor;
   }
   else
   {
      *major = 0;
      *minor = 0;
   }

}