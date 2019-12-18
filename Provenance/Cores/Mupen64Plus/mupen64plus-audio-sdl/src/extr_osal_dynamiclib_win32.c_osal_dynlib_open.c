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
typedef  int /*<<< orphan*/ * m64p_dynlib_handle ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/ * LoadLibrary (char const*) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  M64ERR_INPUT_ASSERT ; 
 int /*<<< orphan*/  M64ERR_INPUT_NOT_FOUND ; 
 int /*<<< orphan*/  M64ERR_SUCCESS ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 

m64p_error osal_dynlib_open(m64p_dynlib_handle *pLibHandle, const char *pccLibraryPath)
{
    if (pLibHandle == NULL || pccLibraryPath == NULL)
        return M64ERR_INPUT_ASSERT;

    *pLibHandle = LoadLibrary(pccLibraryPath);

    if (*pLibHandle == NULL)
    {
        char *pchErrMsg;
        DWORD dwErr = GetLastError(); 
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &pchErrMsg, 0, NULL);
        fprintf(stderr, "LoadLibrary('%s') error: %s\n", pccLibraryPath, pchErrMsg);
        LocalFree(pchErrMsg);
        return M64ERR_INPUT_NOT_FOUND;
    }

    return M64ERR_SUCCESS;
}