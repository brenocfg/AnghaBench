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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cheatlist_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CHEATTYPE_NONE ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__* cheatlist ; 
 int cheatsize ; 

int CheatInit(void)
{  
   cheatsize = 10;
   if ((cheatlist = (cheatlist_struct *)calloc(cheatsize, sizeof(cheatlist_struct))) == NULL)
      return -1;
   cheatlist[0].type = CHEATTYPE_NONE;

   return 0;
}