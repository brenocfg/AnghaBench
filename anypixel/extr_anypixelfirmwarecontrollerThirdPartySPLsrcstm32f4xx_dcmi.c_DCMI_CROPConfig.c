#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int CWSTRTR; int CWSIZER; } ;
struct TYPE_4__ {int DCMI_CaptureCount; scalar_t__ DCMI_VerticalLineCount; scalar_t__ DCMI_VerticalStartLine; scalar_t__ DCMI_HorizontalOffsetCount; } ;
typedef  TYPE_1__ DCMI_CROPInitTypeDef ;

/* Variables and functions */
 TYPE_3__* DCMI ; 

void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct)
{  
  /* Sets the CROP window coordinates */
  DCMI->CWSTRTR = (uint32_t)((uint32_t)DCMI_CROPInitStruct->DCMI_HorizontalOffsetCount |
                  ((uint32_t)DCMI_CROPInitStruct->DCMI_VerticalStartLine << 16));

  /* Sets the CROP window size */
  DCMI->CWSIZER = (uint32_t)(DCMI_CROPInitStruct->DCMI_CaptureCount |
                  ((uint32_t)DCMI_CROPInitStruct->DCMI_VerticalLineCount << 16));
}