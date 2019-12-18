#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ st_mtime; } ;
typedef  TYPE_1__ struct_stat ;
typedef  int curl_off_t ;
struct TYPE_6__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_2__ FILETIME ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CURL_OFF_T_C (int) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 scalar_t__ GetFileTime (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int stat (char const*,TYPE_1__*) ; 
 char* strerror (scalar_t__) ; 

curl_off_t getfiletime(const char *filename, FILE *error_stream)
{
  curl_off_t result = -1;

/* Windows stat() may attempt to adjust the unix GMT file time by a daylight
   saving time offset and since it's GMT that is bad behavior. When we have
   access to a 64-bit type we can bypass stat and get the times directly. */
#if defined(WIN32) && (SIZEOF_CURL_OFF_T >= 8)
  HANDLE hfile;

  hfile = CreateFileA(filename, FILE_READ_ATTRIBUTES,
                      (FILE_SHARE_READ | FILE_SHARE_WRITE |
                       FILE_SHARE_DELETE),
                      NULL, OPEN_EXISTING, 0, NULL);
  if(hfile != INVALID_HANDLE_VALUE) {
    FILETIME ft;
    if(GetFileTime(hfile, NULL, NULL, &ft)) {
      curl_off_t converted = (curl_off_t)ft.dwLowDateTime
          | ((curl_off_t)ft.dwHighDateTime) << 32;

      if(converted < CURL_OFF_T_C(116444736000000000)) {
        fprintf(error_stream,
                "Failed to get filetime: underflow\n");
      }
      else {
        result = (converted - CURL_OFF_T_C(116444736000000000)) / 10000000;
      }
    }
    else {
      fprintf(error_stream,
              "Failed to get filetime: "
              "GetFileTime failed: GetLastError %u\n",
              (unsigned int)GetLastError());
    }
    CloseHandle(hfile);
  }
  else if(GetLastError() != ERROR_FILE_NOT_FOUND) {
    fprintf(error_stream,
            "Failed to get filetime: "
            "CreateFile failed: GetLastError %u\n",
            (unsigned int)GetLastError());
  }
#else
  struct_stat statbuf;
  if(-1 != stat(filename, &statbuf)) {
    result = (curl_off_t)statbuf.st_mtime;
  }
  else if(errno != ENOENT) {
    fprintf(error_stream,
            "Failed to get filetime: %s\n", strerror(errno));
  }
#endif
  return result;
}