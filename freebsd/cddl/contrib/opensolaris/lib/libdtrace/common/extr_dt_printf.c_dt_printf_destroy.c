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
struct TYPE_5__ {struct TYPE_5__* pfv_format; struct TYPE_5__* pfd_next; struct TYPE_5__* pfv_argv; } ;
typedef  TYPE_1__ dt_pfargv_t ;
typedef  TYPE_1__ dt_pfargd_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dt_printf_destroy(dt_pfargv_t *pfv)
{
	dt_pfargd_t *pfd, *nfd;

	for (pfd = pfv->pfv_argv; pfd != NULL; pfd = nfd) {
		nfd = pfd->pfd_next;
		free(pfd);
	}

	free(pfv->pfv_format);
	free(pfv);
}