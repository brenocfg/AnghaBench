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
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int TH_CreateVertex (int /*<<< orphan*/ ) ; 
 int TH_FindVertex (int /*<<< orphan*/ ) ; 

int TH_FindOrCreateVertex(vec3_t v)
{
	int vertexnum;

	vertexnum = TH_FindVertex(v);
	if (!vertexnum) vertexnum = TH_CreateVertex(v);
	return vertexnum;
}