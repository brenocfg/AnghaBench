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
struct loadedfile {char* path; int /*<<< orphan*/  used; scalar_t__ maplen; scalar_t__ len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct loadedfile* bmake_malloc (int) ; 

__attribute__((used)) static struct loadedfile *
loadedfile_create(const char *path)
{
	struct loadedfile *lf;

	lf = bmake_malloc(sizeof(*lf));
	lf->path = (path == NULL ? "(stdin)" : path);
	lf->buf = NULL;
	lf->len = 0;
	lf->maplen = 0;
	lf->used = FALSE;
	return lf;
}