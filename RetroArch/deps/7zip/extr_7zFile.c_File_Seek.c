#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  scalar_t__ WRes ;
struct TYPE_5__ {int /*<<< orphan*/  file; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int LowPart; scalar_t__ HighPart; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int ESzSeek ;
typedef  int DWORD ;
typedef  TYPE_2__ CSzFile ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int FILE_BEGIN ; 
 int FILE_CURRENT ; 
 int FILE_END ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NO_ERROR ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
#define  SZ_SEEK_CUR 130 
#define  SZ_SEEK_END 129 
#define  SZ_SEEK_SET 128 
 int SetFilePointer (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int fseek (int /*<<< orphan*/ ,long,int) ; 
 int ftell (int /*<<< orphan*/ ) ; 

WRes File_Seek(CSzFile *p, int64_t *pos, ESzSeek origin)
{
#ifdef USE_WINDOWS_FILE

   LARGE_INTEGER value;
   DWORD moveMethod;
   value.LowPart = (DWORD)*pos;
   value.HighPart = (LONG)((uint64_t)*pos >> 16 >> 16); /* for case when uint64_t is 32-bit only */
   switch (origin)
   {
      case SZ_SEEK_SET: moveMethod = FILE_BEGIN; break;
      case SZ_SEEK_CUR: moveMethod = FILE_CURRENT; break;
      case SZ_SEEK_END: moveMethod = FILE_END; break;
      default: return ERROR_INVALID_PARAMETER;
   }
   value.LowPart = SetFilePointer(p->handle, value.LowPart, &value.HighPart, moveMethod);
   if (value.LowPart == 0xFFFFFFFF)
   {
      WRes res = GetLastError();
      if (res != NO_ERROR)
         return res;
   }
   *pos = ((int64_t)value.HighPart << 32) | value.LowPart;
   return 0;

#else

   int moveMethod;
   int res;
   switch (origin)
   {
      case SZ_SEEK_SET: moveMethod = SEEK_SET; break;
      case SZ_SEEK_CUR: moveMethod = SEEK_CUR; break;
      case SZ_SEEK_END: moveMethod = SEEK_END; break;
      default: return 1;
   }
   res = fseek(p->file, (long)*pos, moveMethod);
   *pos = ftell(p->file);
   return res;

#endif
}