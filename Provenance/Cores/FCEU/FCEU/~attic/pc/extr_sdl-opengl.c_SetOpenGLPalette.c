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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  HiBuffer ; 
 int /*<<< orphan*/  SetPaletteBlitToHigh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_glColorTableEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * textures ; 

void SetOpenGLPalette(uint8 *data)
{
 if(!HiBuffer)
 {
  p_glBindTexture(GL_TEXTURE_2D, textures[0]);
  p_glColorTableEXT(GL_TEXTURE_2D,GL_RGB,256,GL_RGBA,GL_UNSIGNED_BYTE,data);
 }
 else
  SetPaletteBlitToHigh((uint8*)data); 
}