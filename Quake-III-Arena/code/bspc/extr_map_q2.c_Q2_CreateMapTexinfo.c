#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nexttexinfo; int /*<<< orphan*/  texture; int /*<<< orphan*/  value; int /*<<< orphan*/  flags; int /*<<< orphan*/  vecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  texture; int /*<<< orphan*/  value; int /*<<< orphan*/  flags; int /*<<< orphan*/  vecs; } ;

/* Variables and functions */
 TYPE_2__* map_texinfo ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int numtexinfo ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* texinfo ; 

void Q2_CreateMapTexinfo(void)
{
	int i;

	for (i = 0; i < numtexinfo; i++)
	{
		memcpy(map_texinfo[i].vecs, texinfo[i].vecs, sizeof(float) * 2 * 4);
		map_texinfo[i].flags = texinfo[i].flags;
		map_texinfo[i].value = texinfo[i].value;
		strcpy(map_texinfo[i].texture, texinfo[i].texture);
		map_texinfo[i].nexttexinfo = 0;
	} //end for
}