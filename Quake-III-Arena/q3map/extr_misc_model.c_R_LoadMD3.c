#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* normal; void** xyz; } ;
typedef  TYPE_1__ md3XyzNormal_t ;
struct TYPE_9__ {int* indexes; } ;
typedef  TYPE_2__ md3Triangle_t ;
struct TYPE_10__ {int ident; int flags; int numFrames; int numShaders; int numTriangles; int ofsTriangles; int numVerts; int ofsShaders; int ofsSt; int ofsXyzNormals; int ofsEnd; } ;
typedef  TYPE_3__ md3Surface_t ;
struct TYPE_11__ {void** st; } ;
typedef  TYPE_4__ md3St_t ;
struct TYPE_12__ {int version; int ident; int numFrames; int numTags; int numSurfaces; int numSkins; int ofsFrames; int ofsTags; int ofsSurfaces; int ofsEnd; } ;
typedef  TYPE_5__ md3Header_t ;
struct TYPE_13__ {void** localOrigin; void*** bounds; void* radius; } ;
typedef  TYPE_6__ md3Frame_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char const*,int,int) ; 
 int /*<<< orphan*/  LL (int) ; 
 void* LittleFloat (void*) ; 
 int LittleLong (int) ; 
 void* LittleShort (void*) ; 
 int MD3_VERSION ; 
 int PakLoadAnyFile (char*,void**) ; 
 int SHADER_MAX_INDEXES ; 
 int SHADER_MAX_VERTEXES ; 
 int TryLoadFile (char*,void**) ; 
 int /*<<< orphan*/  _printf (char*,char const*,...) ; 
 char* gamedir ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 

md3Header_t *R_LoadMD3( const char *mod_name ) {
	int					i, j;
	md3Header_t			*md3;
    md3Frame_t			*frame;
	md3Surface_t		*surf;
	md3Triangle_t		*tri;
	md3St_t				*st;
	md3XyzNormal_t		*xyz;
	int					version;
	char				filename[1024];
	int					len;

	sprintf( filename, "%s%s", gamedir, mod_name );
	len = TryLoadFile( filename, (void **)&md3 );
#ifdef _WIN32
  if ( len <= 0 ) {
    len = PakLoadAnyFile(filename, (void **)&md3);
  }
#endif
	if ( len <= 0 ) {
	  return NULL;
	}

  version = LittleLong (md3->version);
	if (version != MD3_VERSION) {
		_printf( "R_LoadMD3: %s has wrong version (%i should be %i)\n",
				 mod_name, version, MD3_VERSION);
		return NULL;
	}

    LL(md3->ident);
    LL(md3->version);
    LL(md3->numFrames);
    LL(md3->numTags);
    LL(md3->numSurfaces);
    LL(md3->numSkins);
    LL(md3->ofsFrames);
    LL(md3->ofsTags);
    LL(md3->ofsSurfaces);
    LL(md3->ofsEnd);

	if ( md3->numFrames < 1 ) {
		_printf( "R_LoadMD3: %s has no frames\n", mod_name );
		return NULL;
	}

    // we don't need to swap tags in the renderer, they aren't used
    
	// swap all the frames
    frame = (md3Frame_t *) ( (byte *)md3 + md3->ofsFrames );
    for ( i = 0 ; i < md3->numFrames ; i++, frame++) {
    	frame->radius = LittleFloat( frame->radius );
        for ( j = 0 ; j < 3 ; j++ ) {
            frame->bounds[0][j] = LittleFloat( frame->bounds[0][j] );
            frame->bounds[1][j] = LittleFloat( frame->bounds[1][j] );
	    	frame->localOrigin[j] = LittleFloat( frame->localOrigin[j] );
        }
	}

	// swap all the surfaces
	surf = (md3Surface_t *) ( (byte *)md3 + md3->ofsSurfaces );
	for ( i = 0 ; i < md3->numSurfaces ; i++) {

        LL(surf->ident);
        LL(surf->flags);
        LL(surf->numFrames);
        LL(surf->numShaders);
        LL(surf->numTriangles);
        LL(surf->ofsTriangles);
        LL(surf->numVerts);
        LL(surf->ofsShaders);
        LL(surf->ofsSt);
        LL(surf->ofsXyzNormals);
        LL(surf->ofsEnd);
		
		if ( surf->numVerts > SHADER_MAX_VERTEXES ) {
			Error ("R_LoadMD3: %s has more than %i verts on a surface (%i)",
				mod_name, SHADER_MAX_VERTEXES, surf->numVerts );
		}
		if ( surf->numTriangles*3 > SHADER_MAX_INDEXES ) {
			Error ("R_LoadMD3: %s has more than %i triangles on a surface (%i)",
				mod_name, SHADER_MAX_INDEXES / 3, surf->numTriangles );
		}

		// swap all the triangles
		tri = (md3Triangle_t *) ( (byte *)surf + surf->ofsTriangles );
		for ( j = 0 ; j < surf->numTriangles ; j++, tri++ ) {
			LL(tri->indexes[0]);
			LL(tri->indexes[1]);
			LL(tri->indexes[2]);
		}

		// swap all the ST
        st = (md3St_t *) ( (byte *)surf + surf->ofsSt );
        for ( j = 0 ; j < surf->numVerts ; j++, st++ ) {
            st->st[0] = LittleFloat( st->st[0] );
            st->st[1] = LittleFloat( st->st[1] );
        }

		// swap all the XyzNormals
        xyz = (md3XyzNormal_t *) ( (byte *)surf + surf->ofsXyzNormals );
        for ( j = 0 ; j < surf->numVerts * surf->numFrames ; j++, xyz++ ) 
		{
            xyz->xyz[0] = LittleShort( xyz->xyz[0] );
            xyz->xyz[1] = LittleShort( xyz->xyz[1] );
            xyz->xyz[2] = LittleShort( xyz->xyz[2] );

            xyz->normal = LittleShort( xyz->normal );
        }


		// find the next surface
		surf = (md3Surface_t *)( (byte *)surf + surf->ofsEnd );
	}

	return md3;
}