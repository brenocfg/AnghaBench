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
typedef  int /*<<< orphan*/  tdesc_t ;
typedef  int /*<<< orphan*/  alist_t ;

/* Variables and functions */
 int /*<<< orphan*/  alist_find (int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdesc_name (void*) ; 

__attribute__((used)) static int
fwd_redir(tdesc_t *fwd, tdesc_t **fwdp, void *private)
{
	alist_t *map = private;
	void *defn;

	if (!alist_find(map, (void *)fwd, (void **)&defn))
		return (0);

	debug(3, "Redirecting an edge to %s\n", tdesc_name(defn));

	*fwdp = defn;

	return (1);
}