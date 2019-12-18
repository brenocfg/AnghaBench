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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ (* NvEncodeAPIGetMaxSupportedVersion ) (int*) ;} ;
typedef  TYPE_1__ NvencFunctions ;
typedef  scalar_t__ NVENCSTATUS ;

/* Variables and functions */
 int NVENCAPI_MAJOR_VERSION ; 
 int NVENCAPI_MINOR_VERSION ; 
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int isAvailable ; 
 scalar_t__ is_hardware_disabled () ; 
 int nvenc_load_functions (TYPE_1__**,void*) ; 
 scalar_t__ stub1 (int*) ; 

int hb_check_nvenc_available()
{
    if (is_hardware_disabled())
    {
        return 0;
    }

    if (isAvailable != -1){
        return isAvailable;
    }

    #if HB_PROJECT_FEATURE_NVENC
        uint32_t nvenc_ver;
        void *context = NULL;
        NvencFunctions *nvenc_dl = NULL;

        int loadErr = nvenc_load_functions(&nvenc_dl, context);
        if (loadErr < 0) {
            isAvailable = 0;
            return 0;
        }

        NVENCSTATUS apiErr = nvenc_dl->NvEncodeAPIGetMaxSupportedVersion(&nvenc_ver);
        if (apiErr != NV_ENC_SUCCESS)
        {
            isAvailable = 0;
            return 0;
        }

        hb_log("Nvenc version %d.%d\n", nvenc_ver >> 4, nvenc_ver & 0xf);
        if ((NVENCAPI_MAJOR_VERSION << 4 | NVENCAPI_MINOR_VERSION) > nvenc_ver) {
            hb_log("NVENC version not supported. Disabling feature.");
            isAvailable = 0;
            return 0;
        }

        isAvailable = 1;
        return 1;
    #else
        return 0;
    #endif
}