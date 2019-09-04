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
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST_MIPMAP_NEAREST ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/ * GenCheckImage (int,int,int) ; 
 int /*<<< orphan*/  GenMipMap2D (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int,int*,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GLuint CreateMipMappedTexture2D( )
{
   // Texture object handle
   GLuint textureId;
   int    width = 256,
          height = 256;
   int    level;
   GLubyte *pixels;
   GLubyte *prevImage;
   GLubyte *newImage;
      
   pixels = GenCheckImage( width, height, 8 );
   if ( pixels == NULL )
      return 0;

   // Generate a texture object
   glGenTextures ( 1, &textureId );

   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );

   // Load mipmap level 0
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 
                  0, GL_RGB, GL_UNSIGNED_BYTE, pixels );
   
   level = 1;
   prevImage = &pixels[0];
   
   while ( width > 1 && height > 1 )
   {
      int newWidth,
          newHeight;

      // Generate the next mipmap level
      GenMipMap2D( prevImage, &newImage, width, height, 
                   &newWidth, &newHeight );

      // Load the mipmap level
      glTexImage2D( GL_TEXTURE_2D, level, GL_RGB, 
                    newWidth, newHeight, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, newImage );

      // Free the previous image
      free ( prevImage );

      // Set the previous image for the next iteration
      prevImage = newImage;
      level++;

      // Half the width and height
      width = newWidth;
      height = newHeight;
   }

   free ( newImage );

   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

   return textureId;

}