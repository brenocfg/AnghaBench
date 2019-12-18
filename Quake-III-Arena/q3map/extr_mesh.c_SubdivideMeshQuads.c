#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int width; int height; TYPE_2__* verts; } ;
typedef  TYPE_1__ mesh_t ;
struct TYPE_13__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ drawVert_t ;

/* Variables and functions */
 TYPE_1__* CopyMesh (TYPE_1__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  LerpDrawVertAmount (TYPE_2__*,TYPE_2__*,float,TYPE_2__*) ; 
 int MAX_EXPANDED_AXIS ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * originalHeights ; 
 int /*<<< orphan*/ * originalWidths ; 

mesh_t *SubdivideMeshQuads( mesh_t *in, float minLength, int maxsize, int widthtable[], int heighttable[]) {
	int			i, j, k, w, h, maxsubdivisions, subdivisions;
	vec3_t		dir;
	float		length, maxLength, amount;
	mesh_t		out;
	drawVert_t	expand[MAX_EXPANDED_AXIS][MAX_EXPANDED_AXIS];

	out.width = in->width;
	out.height = in->height;

	for ( i = 0 ; i < in->width ; i++ ) {
		for ( j = 0 ; j < in->height ; j++ ) {
			expand[j][i] = in->verts[j*in->width+i];
		}
	}

	if (maxsize > MAX_EXPANDED_AXIS)
		Error("SubdivideMeshQuads: maxsize > MAX_EXPANDED_AXIS");

	// horizontal subdivisions

	maxsubdivisions = (maxsize - in->width) / (in->width - 1);

	for ( w = 0, j = 0 ; w < in->width - 1; w++, j += subdivisions + 1) {
		maxLength = 0;
		for ( i = 0 ; i < out.height ; i++ ) {
			VectorSubtract(expand[i][j+1].xyz, expand[i][j].xyz, dir);
			length = VectorLength( dir );
			if (length > maxLength) {
				maxLength = length;
			}
		}
		
		subdivisions = (int) (maxLength / minLength);
		if (subdivisions > maxsubdivisions)
			subdivisions = maxsubdivisions;

		widthtable[w] = subdivisions + 1;
		if (subdivisions <= 0)
			continue;

		out.width += subdivisions;

		for ( k = out.width - 1; k >= j + subdivisions; k-- ) {
			originalWidths[k] = originalWidths[k-subdivisions];
		}
		for (k = 1; k <= subdivisions; k++) {
			originalWidths[j+k] = originalWidths[j];
		}

		for ( i = 0 ; i < out.height ; i++ ) {
			for ( k = out.width - 1 ; k > j + subdivisions; k-- ) {
				expand[i][k] = expand[i][k-subdivisions];
			}
			for (k = 1; k <= subdivisions; k++)
			{
				amount = (float) k / (subdivisions + 1);
				LerpDrawVertAmount(&expand[i][j], &expand[i][j+subdivisions+1], amount, &expand[i][j+k]);
			}
		}
	}

	maxsubdivisions = (maxsize - in->height) / (in->height - 1);

	for ( h = 0, j = 0 ; h < in->height - 1; h++, j += subdivisions + 1) {
		maxLength = 0;
		for ( i = 0 ; i < out.width ; i++ ) {
			VectorSubtract(expand[j+1][i].xyz, expand[j][i].xyz, dir);
			length = VectorLength( dir );
			if (length  > maxLength) {
				maxLength = length;
			}
		}
		
		subdivisions = (int) (maxLength / minLength);
		if (subdivisions > maxsubdivisions)
			subdivisions = maxsubdivisions;

		heighttable[h] = subdivisions + 1;
		if (subdivisions <= 0)
			continue;

		out.height += subdivisions;

		for ( k = out.height - 1; k >= j + subdivisions; k-- ) {
			originalHeights[k] = originalHeights[k-subdivisions];
		}
		for (k = 1; k <= subdivisions; k++) {
			originalHeights[j+k] = originalHeights[j];
		}

		for ( i = 0 ; i < out.width ; i++ ) {
			for ( k = out.height - 1 ; k > j + subdivisions; k-- ) {
				expand[k][i] = expand[k-subdivisions][i];
			}
			for (k = 1; k <= subdivisions; k++)
			{
				amount = (float) k / (subdivisions + 1);
				LerpDrawVertAmount(&expand[j][i], &expand[j+subdivisions+1][i], amount, &expand[j+k][i]);
			}
		}
	}

	// collapse the verts
	out.verts = &expand[0][0];
	for ( i = 1 ; i < out.height ; i++ ) {
		memmove( &out.verts[i*out.width], expand[i], out.width * sizeof(drawVert_t) );
	}

	return CopyMesh(&out);
}