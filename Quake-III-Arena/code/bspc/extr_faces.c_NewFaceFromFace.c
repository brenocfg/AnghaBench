#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * w; int /*<<< orphan*/ ** split; int /*<<< orphan*/ * merged; } ;
typedef  TYPE_1__ face_t ;

/* Variables and functions */
 TYPE_1__* AllocFace () ; 

face_t *NewFaceFromFace (face_t *f)
{
	face_t	*newf;

	newf = AllocFace ();
	*newf = *f;
	newf->merged = NULL;
	newf->split[0] = newf->split[1] = NULL;
	newf->w = NULL;
	return newf;
}