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
typedef  int WRes ;
struct TYPE_3__ {scalar_t__ handle; scalar_t__ file; } ;
typedef  TYPE_1__ CSzFile ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fopen (char const*,char*) ; 

__attribute__((used)) static WRes File_Open(CSzFile *p, const char *name, int writeMode)
{
#ifdef USE_WINDOWS_FILE
   p->handle = CreateFileA(name,
         writeMode ? GENERIC_WRITE : GENERIC_READ,
         FILE_SHARE_READ, NULL,
         writeMode ? CREATE_ALWAYS : OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL, NULL);
   return (p->handle != INVALID_HANDLE_VALUE) ? 0 : GetLastError();
#else
   p->file = fopen(name, writeMode ? "wb+" : "rb");
   return (p->file != 0) ? 0 :
#ifdef UNDER_CE
      2; /* ENOENT */
#else
   errno;
#endif
#endif
}