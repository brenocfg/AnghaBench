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
struct TYPE_5__ {int ESCR; } ;
struct TYPE_4__ {int DCMI_FrameStartCode; scalar_t__ DCMI_FrameEndCode; scalar_t__ DCMI_LineEndCode; scalar_t__ DCMI_LineStartCode; } ;
typedef  TYPE_1__ DCMI_CodesInitTypeDef ;

/* Variables and functions */
 TYPE_3__* DCMI ; 

void DCMI_SetEmbeddedSynchroCodes(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct)
{
  DCMI->ESCR = (uint32_t)(DCMI_CodesInitStruct->DCMI_FrameStartCode |
                          ((uint32_t)DCMI_CodesInitStruct->DCMI_LineStartCode << 8)|
                          ((uint32_t)DCMI_CodesInitStruct->DCMI_LineEndCode << 16)|
                          ((uint32_t)DCMI_CodesInitStruct->DCMI_FrameEndCode << 24));
}