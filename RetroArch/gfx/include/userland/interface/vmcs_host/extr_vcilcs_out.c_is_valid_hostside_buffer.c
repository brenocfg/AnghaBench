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
struct TYPE_3__ {scalar_t__ pBuffer; } ;
typedef  TYPE_1__ OMX_BUFFERHEADERTYPE ;

/* Variables and functions */

__attribute__((used)) static int is_valid_hostside_buffer(OMX_BUFFERHEADERTYPE *pBuf)
{
   if (!pBuf)
      return 0;
   if (!pBuf->pBuffer)
      return 0;
   if ((unsigned long)pBuf->pBuffer < 0x100)
      return 0; // not believable
   return 1;
}