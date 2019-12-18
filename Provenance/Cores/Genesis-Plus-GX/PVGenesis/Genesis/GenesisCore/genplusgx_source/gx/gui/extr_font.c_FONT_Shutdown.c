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

/* Variables and functions */
 scalar_t__ fontHeader ; 
 scalar_t__ fontTexture ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ ipl_fontarea ; 

void FONT_Shutdown(void)
{
  if (fontHeader)
    free(ipl_fontarea);
  if (fontTexture)
    free(fontTexture);
}