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
 scalar_t__ HiBuffer ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  p_glDeleteTextures (int,scalar_t__*) ; 
 scalar_t__* textures ; 

void KillOpenGL(void)
{
 if(textures[0])
  p_glDeleteTextures(2, &textures[0]);
 textures[0]=0;
 if(HiBuffer)
 {
  free(HiBuffer);
  HiBuffer=0;
 }
}