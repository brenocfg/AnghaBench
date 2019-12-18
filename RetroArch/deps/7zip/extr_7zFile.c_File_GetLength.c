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
typedef  int uint64_t ;
typedef  int WRes ;
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  handle; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CSzFile ;

/* Variables and functions */
 int GetFileSize (int /*<<< orphan*/ ,int*) ; 
 int GetLastError () ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 void* ftell (int /*<<< orphan*/ ) ; 

WRes File_GetLength(CSzFile *p, uint64_t *length)
{
#ifdef USE_WINDOWS_FILE

   DWORD sizeHigh;
   DWORD sizeLow = GetFileSize(p->handle, &sizeHigh);
   if (sizeLow == 0xFFFFFFFF)
   {
      DWORD res = GetLastError();
      if (res != NO_ERROR)
         return res;
   }
   *length = (((uint64_t)sizeHigh) << 32) + sizeLow;
   return 0;

#else

   long pos = ftell(p->file);
   int res = fseek(p->file, 0, SEEK_END);
   *length = ftell(p->file);
   fseek(p->file, pos, SEEK_SET);
   return res;

#endif
}