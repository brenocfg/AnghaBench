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
typedef  int uint32_t ;
typedef  int GLenum ;

/* Variables and functions */
#define  GL_PALETTE4_R5_G6_B5_OES 137 
#define  GL_PALETTE4_RGB5_A1_OES 136 
#define  GL_PALETTE4_RGB8_OES 135 
#define  GL_PALETTE4_RGBA4_OES 134 
#define  GL_PALETTE4_RGBA8_OES 133 
#define  GL_PALETTE8_R5_G6_B5_OES 132 
#define  GL_PALETTE8_RGB5_A1_OES 131 
#define  GL_PALETTE8_RGB8_OES 130 
#define  GL_PALETTE8_RGBA4_OES 129 
#define  GL_PALETTE8_RGBA8_OES 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

__attribute__((used)) static uint32_t get_palette_size(GLenum internalformat)
{
   switch (internalformat)
   {
   case GL_PALETTE4_RGB8_OES: return 16 * 3;
   case GL_PALETTE4_RGBA8_OES: return 16 * 4;
   case GL_PALETTE4_R5_G6_B5_OES: return 16 * 2;
   case GL_PALETTE4_RGBA4_OES: return 16 * 2;
   case GL_PALETTE4_RGB5_A1_OES: return 16 * 2;
   case GL_PALETTE8_RGB8_OES: return 256 * 3;
   case GL_PALETTE8_RGBA8_OES: return 256 * 4;
   case GL_PALETTE8_R5_G6_B5_OES: return 256 * 2;
   case GL_PALETTE8_RGBA4_OES: return 256 * 2;
   case GL_PALETTE8_RGB5_A1_OES: return 256 * 2;
   default:
      UNREACHABLE();
      return 0;
   }
}