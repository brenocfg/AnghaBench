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
typedef  int /*<<< orphan*/  uint8_t ;
struct proc {int /*<<< orphan*/  p_textoff; int /*<<< orphan*/ * p_textvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  csvnode_get_platform_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint8_t
csproc_get_platform_identifier(struct proc *p)
{
	if (NULL == p->p_textvp)
		return 0;

	return csvnode_get_platform_identifier(p->p_textvp, p->p_textoff);
}