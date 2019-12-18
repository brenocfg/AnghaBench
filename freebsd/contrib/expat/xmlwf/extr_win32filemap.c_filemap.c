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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFile (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMapping (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_SEQUENTIAL_SCAN ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 void* MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  UnmapViewOfFile (void*) ; 
 scalar_t__ XML_MAX_CHUNK_LEN ; 
 int /*<<< orphan*/  win32perror (int /*<<< orphan*/  const*) ; 

int
filemap(const TCHAR *name,
        void (*processor)(const void *, size_t, const TCHAR *, void *arg),
        void *arg)
{
  HANDLE f;
  HANDLE m;
  DWORD size;
  DWORD sizeHi;
  void *p;

  f = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                          FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  if (f == INVALID_HANDLE_VALUE) {
    win32perror(name);
    return 0;
  }
  size = GetFileSize(f, &sizeHi);
  if (size == (DWORD)-1) {
    win32perror(name);
    CloseHandle(f);
    return 0;
  }
  if (sizeHi || (size > XML_MAX_CHUNK_LEN)) {
    CloseHandle(f);
    return 2;  /* Cannot be passed to XML_Parse in one go */
  }
  /* CreateFileMapping barfs on zero length files */
  if (size == 0) {
    static const char c = '\0';
    processor(&c, 0, name, arg);
    CloseHandle(f);
    return 1;
  }
  m = CreateFileMapping(f, NULL, PAGE_READONLY, 0, 0, NULL);
  if (m == NULL) {
    win32perror(name);
    CloseHandle(f);
    return 0;
  }
  p = MapViewOfFile(m, FILE_MAP_READ, 0, 0, 0);
  if (p == NULL) {
    win32perror(name);
    CloseHandle(m);
    CloseHandle(f);
    return 0;
  }
  processor(p, size, name, arg); 
  UnmapViewOfFile(p);
  CloseHandle(m);
  CloseHandle(f);
  return 1;
}