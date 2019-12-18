#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** str_bufs; int str_nbufs; char* str_ptr; int /*<<< orphan*/  str_bufsz; } ;
typedef  TYPE_1__ dt_strtab_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 char** realloc (char**,int) ; 

__attribute__((used)) static int
dt_strtab_grow(dt_strtab_t *sp)
{
	char *ptr, **bufs;

	if ((ptr = malloc(sp->str_bufsz)) == NULL)
		return (-1);

	bufs = realloc(sp->str_bufs, (sp->str_nbufs + 1) * sizeof (char *));

	if (bufs == NULL) {
		free(ptr);
		return (-1);
	}

	sp->str_nbufs++;
	sp->str_bufs = bufs;
	sp->str_ptr = ptr;
	sp->str_bufs[sp->str_nbufs - 1] = sp->str_ptr;

	return (0);
}