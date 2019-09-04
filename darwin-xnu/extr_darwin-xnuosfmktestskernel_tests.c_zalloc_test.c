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
typedef  void* zone_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_PERF (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  threads_count ; 
 void* zalloc (void*) ; 
 int /*<<< orphan*/  zfree (void*,void*) ; 
 void* zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_free_count (void*) ; 

kern_return_t
zalloc_test()
{
	zone_t test_zone;
	void * test_ptr;

	T_SETUPBEGIN;
	test_zone = zinit(sizeof(uint64_t), 100 * sizeof(uint64_t), sizeof(uint64_t), "test_uint64_zone");
	T_ASSERT_NOTNULL(test_zone, NULL);

	T_ASSERT_EQ_INT(zone_free_count(test_zone), 0, NULL);
	T_SETUPEND;

	T_ASSERT_NOTNULL(test_ptr = zalloc(test_zone), NULL);

	zfree(test_zone, test_ptr);

	/* A sample report for perfdata */
	T_PERF("num_threads_at_ktest", threads_count, "count", "# of threads in system at zalloc_test");

	return KERN_SUCCESS;
}