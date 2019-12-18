#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int realtime; int frametime; } ;

/* Variables and functions */
 int UI_DROPSHADOW ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char const*,int,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int /*<<< orphan*/  UI_PrintTime (char*,int,int) ; 
 int UI_ProportionalSizeScale (int) ; 
 int UI_ProportionalStringWidth (char*) ; 
 int /*<<< orphan*/  UI_ReadableSize (char*,int,int) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  color_white ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int trap_Cvar_VariableValue (char*) ; 
 TYPE_1__ uis ; 
 char* va (char*,char const*,...) ; 

__attribute__((used)) static void UI_DisplayDownloadInfo( const char *downloadName ) {
	static char dlText[]	= "Downloading:";
	static char etaText[]	= "Estimated time left:";
	static char xferText[]	= "Transfer rate:";

	int downloadSize, downloadCount, downloadTime;
	char dlSizeBuf[64], totalSizeBuf[64], xferRateBuf[64], dlTimeBuf[64];
	int xferRate;
	int width, leftWidth;
	int style = UI_LEFT|UI_SMALLFONT|UI_DROPSHADOW;
	const char *s;

	downloadSize = trap_Cvar_VariableValue( "cl_downloadSize" );
	downloadCount = trap_Cvar_VariableValue( "cl_downloadCount" );
	downloadTime = trap_Cvar_VariableValue( "cl_downloadTime" );

#if 0 // bk010104
	fprintf( stderr, "\n\n-----------------------------------------------\n");
	fprintf( stderr, "DB: downloadSize:  %16d\n", downloadSize );
	fprintf( stderr, "DB: downloadCount: %16d\n", downloadCount );
	fprintf( stderr, "DB: downloadTime:  %16d\n", downloadTime );  
  	fprintf( stderr, "DB: UI realtime:   %16d\n", uis.realtime );	// bk
	fprintf( stderr, "DB: UI frametime:  %16d\n", uis.frametime );	// bk
#endif

	leftWidth = width = UI_ProportionalStringWidth( dlText ) * UI_ProportionalSizeScale( style );
	width = UI_ProportionalStringWidth( etaText ) * UI_ProportionalSizeScale( style );
	if (width > leftWidth) leftWidth = width;
	width = UI_ProportionalStringWidth( xferText ) * UI_ProportionalSizeScale( style );
	if (width > leftWidth) leftWidth = width;
	leftWidth += 16;

	UI_DrawProportionalString( 8, 128, dlText, style, color_white );
	UI_DrawProportionalString( 8, 160, etaText, style, color_white );
	UI_DrawProportionalString( 8, 224, xferText, style, color_white );

	if (downloadSize > 0) {
		s = va( "%s (%d%%)", downloadName, downloadCount * 100 / downloadSize );
	} else {
		s = downloadName;
	}

	UI_DrawProportionalString( leftWidth, 128, s, style, color_white );

	UI_ReadableSize( dlSizeBuf,		sizeof dlSizeBuf,		downloadCount );
	UI_ReadableSize( totalSizeBuf,	sizeof totalSizeBuf,	downloadSize );

	if (downloadCount < 4096 || !downloadTime) {
		UI_DrawProportionalString( leftWidth, 160, "estimating", style, color_white );
		UI_DrawProportionalString( leftWidth, 192, 
			va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), style, color_white );
	} else {
	  // bk010108
	  //float elapsedTime = (float)(uis.realtime - downloadTime); // current - start (msecs)
	  //elapsedTime = elapsedTime * 0.001f; // in seconds
	  //if ( elapsedTime <= 0.0f ) elapsedTime == 0.0f;
	  if ( (uis.realtime - downloadTime) / 1000) {
			xferRate = downloadCount / ((uis.realtime - downloadTime) / 1000);
		  //xferRate = (int)( ((float)downloadCount) / elapsedTime);
		} else {
			xferRate = 0;
		}

	  //fprintf( stderr, "DB: elapsedTime:  %16.8f\n", elapsedTime );	// bk
	  //fprintf( stderr, "DB: xferRate:   %16d\n", xferRate );	// bk

		UI_ReadableSize( xferRateBuf, sizeof xferRateBuf, xferRate );

		// Extrapolate estimated completion time
		if (downloadSize && xferRate) {
			int n = downloadSize / xferRate; // estimated time for entire d/l in secs

			// We do it in K (/1024) because we'd overflow around 4MB
			n = (n - (((downloadCount/1024) * n) / (downloadSize/1024))) * 1000;
			
			UI_PrintTime ( dlTimeBuf, sizeof dlTimeBuf, n ); // bk010104
				//(n - (((downloadCount/1024) * n) / (downloadSize/1024))) * 1000);

			UI_DrawProportionalString( leftWidth, 160, 
				dlTimeBuf, style, color_white );
			UI_DrawProportionalString( leftWidth, 192, 
				va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), style, color_white );
		} else {
			UI_DrawProportionalString( leftWidth, 160, 
				"estimating", style, color_white );
			if (downloadSize) {
				UI_DrawProportionalString( leftWidth, 192, 
					va("(%s of %s copied)", dlSizeBuf, totalSizeBuf), style, color_white );
			} else {
				UI_DrawProportionalString( leftWidth, 192, 
					va("(%s copied)", dlSizeBuf), style, color_white );
			}
		}

		if (xferRate) {
			UI_DrawProportionalString( leftWidth, 224, 
				va("%s/Sec", xferRateBuf), style, color_white );
		}
	}
}