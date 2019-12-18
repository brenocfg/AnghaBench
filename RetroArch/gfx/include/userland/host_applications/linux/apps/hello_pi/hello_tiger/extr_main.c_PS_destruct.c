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
struct TYPE_5__ {int m_numPaths; struct TYPE_5__* m_paths; int /*<<< orphan*/  m_path; int /*<<< orphan*/  m_strokePaint; int /*<<< orphan*/  m_fillPaint; } ;
typedef  TYPE_1__ PS ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vgDestroyPaint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDestroyPath (int /*<<< orphan*/ ) ; 

void PS_destruct(PS* ps)
{
	int i;
	assert(ps);
	for(i=0;i<ps->m_numPaths;i++)
	{
		vgDestroyPaint(ps->m_paths[i].m_fillPaint);
		vgDestroyPaint(ps->m_paths[i].m_strokePaint);
		vgDestroyPath(ps->m_paths[i].m_path);
	}
	free(ps->m_paths);
	free(ps);
}