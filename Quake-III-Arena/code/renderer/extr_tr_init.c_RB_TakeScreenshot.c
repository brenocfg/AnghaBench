#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_6__ {int vidWidth; int vidHeight; scalar_t__ deviceSupportsGamma; } ;
struct TYPE_5__ {int* (* Hunk_AllocateTempMemory ) (int) ;int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (int*) ;int /*<<< orphan*/  (* FS_WriteFile ) (char*,int*,int) ;} ;
struct TYPE_4__ {scalar_t__ overbrightBits; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  R_GammaCorrect (int*,int) ; 
 TYPE_3__ glConfig ; 
 int /*<<< orphan*/  qglReadPixels (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__ ri ; 
 int* stub1 (int) ; 
 int /*<<< orphan*/  stub2 (char*,int*,int) ; 
 int /*<<< orphan*/  stub3 (int*) ; 
 TYPE_1__ tr ; 

void RB_TakeScreenshot( int x, int y, int width, int height, char *fileName ) {
	byte		*buffer;
	int			i, c, temp;
		
	buffer = ri.Hunk_AllocateTempMemory(glConfig.vidWidth*glConfig.vidHeight*3+18);

	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 24;	// pixel size

	qglReadPixels( x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer+18 ); 

	// swap rgb to bgr
	c = 18 + width * height * 3;
	for (i=18 ; i<c ; i+=3) {
		temp = buffer[i];
		buffer[i] = buffer[i+2];
		buffer[i+2] = temp;
	}

	// gamma correct
	if ( ( tr.overbrightBits > 0 ) && glConfig.deviceSupportsGamma ) {
		R_GammaCorrect( buffer + 18, glConfig.vidWidth * glConfig.vidHeight * 3 );
	}

	ri.FS_WriteFile( fileName, buffer, c );

	ri.Hunk_FreeTempMemory( buffer );
}