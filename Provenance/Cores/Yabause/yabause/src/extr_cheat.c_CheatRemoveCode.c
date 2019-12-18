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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int CheatRemoveCodeByIndex (int) ; 
 int FindCheat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CheatRemoveCode(int type, u32 addr, u32 val)
{
   int i;

   if ((i = FindCheat(type, addr, val)) == -1)
      // There is no matches, so let's bail
      return -1;

   return CheatRemoveCodeByIndex(i);
}