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
typedef  int /*<<< orphan*/  shaderInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_TERRAIN_TEXTURES ; 
 int numtextures ; 
 int /*<<< orphan*/ ** textures ; 

void Terrain_AddTexture( shaderInfo_t *texture ) {
	int i;

	if ( !texture ) {
		return;
	}

	for( i = 0; i < numtextures; i++ ) {
		if ( textures[ i ] == texture ) {
			return;
		}
	}

	if ( numtextures >= MAX_TERRAIN_TEXTURES ) {
		Error( "Too many textures on terrain" );
		return;
	}

	textures[ numtextures++ ] = texture;
}