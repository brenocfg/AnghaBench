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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_X ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_X ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_Y ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_Z ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GLuint CreateSimpleTextureCubemap( )
{
   GLuint textureId;
   // Six 1x1 RGB faces
   GLubyte cubePixels[6][3] =
   {
      // Face 0 - Red
      255, 0, 0,
      // Face 1 - Green,
      0, 255, 0, 
      // Face 3 - Blue
      0, 0, 255,
      // Face 4 - Yellow
      255, 255, 0,
      // Face 5 - Purple
      255, 0, 255,
      // Face 6 - White
      255, 255, 255
   };
   
   // Generate a texture object
   glGenTextures ( 1, &textureId );

   // Bind the texture object
   glBindTexture ( GL_TEXTURE_CUBE_MAP, textureId );
   
   // Load the cube face - Positive X
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[0] );

   // Load the cube face - Negative X
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[1] );

   // Load the cube face - Positive Y
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[2] );

   // Load the cube face - Negative Y
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[3] );

   // Load the cube face - Positive Z
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[4] );

   // Load the cube face - Negative Z
   glTexImage2D ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, 1, 1, 0, 
                  GL_RGB, GL_UNSIGNED_BYTE, &cubePixels[5] );

   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

   return textureId;

}