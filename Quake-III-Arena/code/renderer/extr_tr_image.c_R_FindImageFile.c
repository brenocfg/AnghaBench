#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {char* imgName; int wrapClampMode; int /*<<< orphan*/  allowPicmip; int /*<<< orphan*/  mipmap; struct TYPE_6__* next; } ;
typedef  TYPE_1__ image_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_7__ {int /*<<< orphan*/  (* Free ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 TYPE_1__* R_CreateImage (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R_LoadImage (char const*,int /*<<< orphan*/ **,int*,int*) ; 
 long generateHashValue (char const*) ; 
 TYPE_1__** hashTable ; 
 TYPE_2__ ri ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 char toupper (char) ; 

image_t	*R_FindImageFile( const char *name, qboolean mipmap, qboolean allowPicmip, int glWrapClampMode ) {
	image_t	*image;
	int		width, height;
	byte	*pic;
	long	hash;

	if (!name) {
		return NULL;
	}

	hash = generateHashValue(name);

	//
	// see if the image is already loaded
	//
	for (image=hashTable[hash]; image; image=image->next) {
		if ( !strcmp( name, image->imgName ) ) {
			// the white image can be used with any set of parms, but other mismatches are errors
			if ( strcmp( name, "*white" ) ) {
				if ( image->mipmap != mipmap ) {
					ri.Printf( PRINT_DEVELOPER, "WARNING: reused image %s with mixed mipmap parm\n", name );
				}
				if ( image->allowPicmip != allowPicmip ) {
					ri.Printf( PRINT_DEVELOPER, "WARNING: reused image %s with mixed allowPicmip parm\n", name );
				}
				if ( image->wrapClampMode != glWrapClampMode ) {
					ri.Printf( PRINT_ALL, "WARNING: reused image %s with mixed glWrapClampMode parm\n", name );
				}
			}
			return image;
		}
	}

	//
	// load the pic from disk
	//
	R_LoadImage( name, &pic, &width, &height );
	if ( pic == NULL ) {                                    // if we dont get a successful load
	  char altname[MAX_QPATH];                              // copy the name
    int len;                                              //  
    strcpy( altname, name );                              //
    len = strlen( altname );                              // 
    altname[len-3] = toupper(altname[len-3]);             // and try upper case extension for unix systems
    altname[len-2] = toupper(altname[len-2]);             //
    altname[len-1] = toupper(altname[len-1]);             //
		ri.Printf( PRINT_ALL, "trying %s...\n", altname );    // 
	  R_LoadImage( altname, &pic, &width, &height );        //
    if (pic == NULL) {                                    // if that fails
      return NULL;                                        // bail
    }
	}

	image = R_CreateImage( ( char * ) name, pic, width, height, mipmap, allowPicmip, glWrapClampMode );
	ri.Free( pic );
	return image;
}