#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_7__ {TYPE_1__* w; scalar_t__* split; scalar_t__ merged; } ;
typedef  TYPE_2__ face_t ;
struct TYPE_8__ {int /*<<< orphan*/  point; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  FaceFromSuperverts (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t GetVertexnum (int /*<<< orphan*/ ) ; 
 size_t MAX_MAP_VERTS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_totalverts ; 
 int /*<<< orphan*/  c_uniqueverts ; 
 TYPE_3__* dvertexes ; 
 scalar_t__ noweld ; 
 int numsuperverts ; 
 size_t numvertexes ; 
 size_t* superverts ; 

void EmitFaceVertexes (node_t *node, face_t *f)
{
	winding_t	*w;
	int			i;

	if (f->merged || f->split[0] || f->split[1])
		return;

	w = f->w;
	for (i=0 ; i<w->numpoints ; i++)
	{
		if (noweld)
		{	// make every point unique
			if (numvertexes == MAX_MAP_VERTS)
				Error ("MAX_MAP_VERTS");
			superverts[i] = numvertexes;
			VectorCopy (w->p[i], dvertexes[numvertexes].point);
			numvertexes++;
			c_uniqueverts++;
			c_totalverts++;
		}
		else
			superverts[i] = GetVertexnum (w->p[i]);
	}
	numsuperverts = w->numpoints;

	// this may fragment the face if > MAXEDGES
	FaceFromSuperverts (node, f, 0);
}