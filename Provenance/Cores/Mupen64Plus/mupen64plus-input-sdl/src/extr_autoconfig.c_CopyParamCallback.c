#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int m64p_type ;
struct TYPE_2__ {int /*<<< orphan*/  pDst; int /*<<< orphan*/  pSrc; } ;
typedef  TYPE_1__ SCopySection ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigGetParameter (int /*<<< orphan*/ ,char const*,int,...) ; 
 int /*<<< orphan*/  ConfigSetParameter (int /*<<< orphan*/ ,char const*,int,...) ; 
 int /*<<< orphan*/  DebugMessage (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  M64ERR_SUCCESS ; 
 int /*<<< orphan*/  M64MSG_ERROR ; 
#define  M64TYPE_BOOL 131 
#define  M64TYPE_FLOAT 130 
#define  M64TYPE_INT 129 
#define  M64TYPE_STRING 128 

__attribute__((used)) static void CopyParamCallback(void * context, const char *ParamName, m64p_type ParamType)
{
    SCopySection *pCpyContext = (SCopySection *) context;
    int paramInt;
    float paramFloat;
    char paramString[1024];

    // handle the parameter copy depending upon type
    switch (ParamType)
    {
        case M64TYPE_INT:
        case M64TYPE_BOOL:
            if (ConfigGetParameter(pCpyContext->pSrc, ParamName, ParamType, &paramInt, sizeof(int)) == M64ERR_SUCCESS)
                ConfigSetParameter(pCpyContext->pDst, ParamName, ParamType, &paramInt);
            break;
        case M64TYPE_FLOAT:
            if (ConfigGetParameter(pCpyContext->pSrc, ParamName, ParamType, &paramFloat, sizeof(float)) == M64ERR_SUCCESS)
                ConfigSetParameter(pCpyContext->pDst, ParamName, ParamType, &paramFloat);
            break;
        case M64TYPE_STRING:
            if (ConfigGetParameter(pCpyContext->pSrc, ParamName, ParamType, paramString, 1024) == M64ERR_SUCCESS)
                ConfigSetParameter(pCpyContext->pDst, ParamName, ParamType, paramString);
            break;
        default:
            // this should never happen
            DebugMessage(M64MSG_ERROR, "Unknown source parameter type %i in copy callback", (int) ParamType);
            return;
    }
}