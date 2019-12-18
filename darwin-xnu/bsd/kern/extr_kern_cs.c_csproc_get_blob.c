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
struct proc {int p_csflags; int /*<<< orphan*/  p_textoff; int /*<<< orphan*/ * p_textvp; } ;
struct cs_blob {int dummy; } ;

/* Variables and functions */
 int CS_SIGNED ; 
 struct cs_blob* ubc_cs_blob_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

struct cs_blob *
csproc_get_blob(struct proc *p)
{
	if (NULL == p)
		return NULL;

	if (NULL == p->p_textvp)
		return NULL;

	if ((p->p_csflags & CS_SIGNED) == 0) {
		return NULL;
	}

	return ubc_cs_blob_get(p->p_textvp, -1, p->p_textoff);
}