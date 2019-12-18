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
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 TYPE_1__* M68K ; 
 TYPE_1__** M68KCoreList ; 
 TYPE_1__ M68KDummy ; 

int M68KInit(int coreid) {
   int i;

   M68K = &M68KDummy;

   // Go through core list and find the id
   for (i = 0; M68KCoreList[i] != NULL; i++)
   {
      if (M68KCoreList[i]->id == coreid)
      {
         // Set to current core
         M68K = M68KCoreList[i];
         break;
      }
   }

   return 0;
}