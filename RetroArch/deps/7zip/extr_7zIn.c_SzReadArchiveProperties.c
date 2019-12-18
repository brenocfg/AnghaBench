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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  CSzData ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzReadID (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  SzSkeepData (int /*<<< orphan*/ *) ; 
 scalar_t__ k7zIdEnd ; 

__attribute__((used)) static SRes SzReadArchiveProperties(CSzData *sd)
{
   for (;;)
   {
      uint64_t type;
      RINOK(SzReadID(sd, &type));
      if (type == k7zIdEnd)
         break;
      SzSkeepData(sd);
   }
   return SZ_OK;
}