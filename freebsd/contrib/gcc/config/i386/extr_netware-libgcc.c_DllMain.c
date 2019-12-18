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
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AllocSignature ; 
 int /*<<< orphan*/ * AllocateResourceTag (void*,char*,int /*<<< orphan*/ ) ; 
#define  DLL_NLM_SHUTDOWN 129 
#define  DLL_NLM_STARTUP 128 
 int /*<<< orphan*/ * allocRTag ; 

BOOL
DllMain (HINSTANCE libraryId __attribute__ ((__unused__)),
	 DWORD reason, void *hModule)
{
  switch (reason)
    {
    case DLL_NLM_STARTUP:
      allocRTag = AllocateResourceTag (hModule,
				       "libgcc memory", AllocSignature);
      return allocRTag != NULL;
    case DLL_NLM_SHUTDOWN:
      /* This does not recover resources associated with the tag...
         ReturnResourceTag (allocRTag, 0); */
      break;
    }
  return 1;
}