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
struct MY_STAT {scalar_t__ st_nlink; } ;
typedef  scalar_t__ IntNative ;
typedef  scalar_t__ Int32 ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ MY_LSTAT (int /*<<< orphan*/ *,struct MY_STAT*) ; 

__attribute__((used)) static 
Int32 countHardLinks ( Char* name )
{  
   IntNative      i;
   struct MY_STAT statBuf;

   i = MY_LSTAT ( name, &statBuf );
   if (i != 0) return 0;
   return (statBuf.st_nlink - 1);
}