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
typedef  scalar_t__ OMX_COMMANDTYPE ;

/* Variables and functions */
 size_t MMALOMX_SAT (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vcos_countof (char const**) ; 

const char *mmalomx_cmd_to_string(OMX_COMMANDTYPE cmd)
{
  static const char *names[] = {
    "OMX_CommandStateSet", "OMX_CommandFlush", "OMX_CommandPortDisable",
    "OMX_CommandPortEnable", "OMX_CommandMarkBuffer", "OMX_Command unknown"
  };

  return names[MMALOMX_SAT((int)cmd, 0, (int)vcos_countof(names)-1)];
}