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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  LoadBMP (char const*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  LoadJPG (char const*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  LoadPCX32 (char const*,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  LoadTGA (char const*,int /*<<< orphan*/ **,int*,int*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

void R_LoadImage( const char *name, byte **pic, int *width, int *height ) {
	int		len;

	*pic = NULL;
	*width = 0;
	*height = 0;

	len = strlen(name);
	if (len<5) {
		return;
	}

	if ( !Q_stricmp( name+len-4, ".tga" ) ) {
	  LoadTGA( name, pic, width, height );            // try tga first
    if (!*pic) {                                    //
		  char altname[MAX_QPATH];                      // try jpg in place of tga 
      strcpy( altname, name );                      
      len = strlen( altname );                  
      altname[len-3] = 'j';
      altname[len-2] = 'p';
      altname[len-1] = 'g';
			LoadJPG( altname, pic, width, height );
		}
  } else if ( !Q_stricmp(name+len-4, ".pcx") ) {
    LoadPCX32( name, pic, width, height );
	} else if ( !Q_stricmp( name+len-4, ".bmp" ) ) {
		LoadBMP( name, pic, width, height );
	} else if ( !Q_stricmp( name+len-4, ".jpg" ) ) {
		LoadJPG( name, pic, width, height );
	}
}