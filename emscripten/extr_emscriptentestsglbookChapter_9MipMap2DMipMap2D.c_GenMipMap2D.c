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
typedef  scalar_t__ GLubyte ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__* malloc (int) ; 

GLboolean GenMipMap2D( GLubyte *src, GLubyte **dst, int srcWidth, int srcHeight, int *dstWidth, int *dstHeight )
{
   int x,
       y;
   int texelSize = 3;

   *dstWidth = srcWidth / 2;
   if ( *dstWidth <= 0 )
      *dstWidth = 1;

   *dstHeight = srcHeight / 2;
   if ( *dstHeight <= 0 )
      *dstHeight = 1;

   *dst = malloc ( sizeof(GLubyte) * texelSize * (*dstWidth) * (*dstHeight) );
   if ( *dst == NULL )
      return GL_FALSE;

   for ( y = 0; y < *dstHeight; y++ )
   {
      for( x = 0; x < *dstWidth; x++ )
      {
         int srcIndex[4];
         float r = 0.0f,
               g = 0.0f,
               b = 0.0f;
         int sample;

         // Compute the offsets for 2x2 grid of pixels in previous
         // image to perform box filter
         srcIndex[0] = 
            (((y * 2) * srcWidth) + (x * 2)) * texelSize;
         srcIndex[1] = 
            (((y * 2) * srcWidth) + (x * 2 + 1)) * texelSize; 
         srcIndex[2] = 
            ((((y * 2) + 1) * srcWidth) + (x * 2)) * texelSize;
         srcIndex[3] = 
            ((((y * 2) + 1) * srcWidth) + (x * 2 + 1)) * texelSize;

         // Sum all pixels
         for ( sample = 0; sample < 4; sample++ )
         {
            r += src[srcIndex[sample]];
            g += src[srcIndex[sample] + 1];
            b += src[srcIndex[sample] + 2];
         }

         // Average results
         r /= 4.0;
         g /= 4.0;
         b /= 4.0;

         // Store resulting pixels
         (*dst)[ ( y * (*dstWidth) + x ) * texelSize ] = (GLubyte)( r );
         (*dst)[ ( y * (*dstWidth) + x ) * texelSize + 1] = (GLubyte)( g );
         (*dst)[ ( y * (*dstWidth) + x ) * texelSize + 2] = (GLubyte)( b );
      }
   }

   return GL_TRUE;
}