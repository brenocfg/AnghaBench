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
typedef  int /*<<< orphan*/  m64p_error ;
typedef  int /*<<< orphan*/  m64p_dynlib_handle ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  M64ERR_INTERNAL ; 
 int /*<<< orphan*/  M64ERR_SUCCESS ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

m64p_error osal_dynlib_close(m64p_dynlib_handle LibHandle)
{
    int rval = FreeLibrary(LibHandle);

    if (rval == 0)
    {
        char *pchErrMsg;
        DWORD dwErr = GetLastError(); 
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &pchErrMsg, 0, NULL);
        fprintf(stderr, "FreeLibrary() error: %s\n", pchErrMsg);
        LocalFree(pchErrMsg);
        return M64ERR_INTERNAL;
    }

    return M64ERR_SUCCESS;
}