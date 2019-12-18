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
typedef  int /*<<< orphan*/  writewordfunc ;
typedef  int /*<<< orphan*/  writelongfunc ;
typedef  int /*<<< orphan*/  writebytefunc ;
typedef  int /*<<< orphan*/  readwordfunc ;
typedef  int /*<<< orphan*/  readlongfunc ;
typedef  int /*<<< orphan*/  readbytefunc ;

/* Variables and functions */
 int /*<<< orphan*/ * ReadByteList ; 
 int /*<<< orphan*/ * ReadLongList ; 
 int /*<<< orphan*/ * ReadWordList ; 
 int /*<<< orphan*/ * WriteByteList ; 
 int /*<<< orphan*/ * WriteLongList ; 
 int /*<<< orphan*/ * WriteWordList ; 

__attribute__((used)) static void FillMemoryArea(unsigned short start, unsigned short end,
                           readbytefunc r8func, readwordfunc r16func,
                           readlongfunc r32func, writebytefunc w8func,
                           writewordfunc w16func, writelongfunc w32func)
{
   int i;

   for (i=start; i < (end+1); i++)
   {
      ReadByteList[i] = r8func;
      ReadWordList[i] = r16func;
      ReadLongList[i] = r32func;
      WriteByteList[i] = w8func;
      WriteWordList[i] = w16func;
      WriteLongList[i] = w32func;
   }
}