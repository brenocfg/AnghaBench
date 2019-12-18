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
typedef  int /*<<< orphan*/  main_arena_ind ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  arena_ind ;

/* Variables and functions */
 int BUFERROR_BUF ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_u_eq (unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  buferror (int,char*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int mallctl (char*,unsigned int*,size_t*,unsigned int*,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  test_fail (char*,char*) ; 

void *
thd_start(void *arg)
{
	unsigned main_arena_ind = *(unsigned *)arg;
	void *p;
	unsigned arena_ind;
	size_t size;
	int err;

	p = malloc(1);
	assert_ptr_not_null(p, "Error in malloc()");
	free(p);

	size = sizeof(arena_ind);
	if ((err = mallctl("thread.arena", &arena_ind, &size, &main_arena_ind,
	    sizeof(main_arena_ind)))) {
		char buf[BUFERROR_BUF];

		buferror(err, buf, sizeof(buf));
		test_fail("Error in mallctl(): %s", buf);
	}

	size = sizeof(arena_ind);
	if ((err = mallctl("thread.arena", &arena_ind, &size, NULL, 0))) {
		char buf[BUFERROR_BUF];

		buferror(err, buf, sizeof(buf));
		test_fail("Error in mallctl(): %s", buf);
	}
	assert_u_eq(arena_ind, main_arena_ind,
	    "Arena index should be same as for main thread");

	return (NULL);
}