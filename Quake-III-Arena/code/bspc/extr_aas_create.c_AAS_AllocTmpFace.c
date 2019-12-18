#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* l_prev; struct TYPE_4__* l_next; scalar_t__ num; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_5__ {int /*<<< orphan*/  numfaces; TYPE_1__* faces; int /*<<< orphan*/  facenum; } ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_2__ tmpaasworld ; 

tmp_face_t *AAS_AllocTmpFace(void)
{
	tmp_face_t *tmpface;

	tmpface = (tmp_face_t *) GetClearedMemory(sizeof(tmp_face_t));
	tmpface->num = tmpaasworld.facenum++;
	tmpface->l_prev = NULL;
	tmpface->l_next = tmpaasworld.faces;
	if (tmpaasworld.faces) tmpaasworld.faces->l_prev = tmpface;
	tmpaasworld.faces = tmpface;
	tmpaasworld.numfaces++;
	return tmpface;
}