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
struct fscache_state {int dummy; } ;
struct fscache_object {int dummy; } ;

/* Variables and functions */
 struct fscache_state* _fscache_invalidate_object (struct fscache_object*,int) ; 
 int /*<<< orphan*/  fscache_n_cop_invalidate_object ; 
 int /*<<< orphan*/  fscache_n_invalidates_run ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct fscache_state *fscache_invalidate_object(struct fscache_object *object,
							     int event)
{
	const struct fscache_state *s;

	fscache_stat(&fscache_n_invalidates_run);
	fscache_stat(&fscache_n_cop_invalidate_object);
	s = _fscache_invalidate_object(object, event);
	fscache_stat_d(&fscache_n_cop_invalidate_object);
	return s;
}