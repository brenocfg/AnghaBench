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
struct core_name {char* corename; int size; } ;

/* Variables and functions */
 int CORENAME_MAX_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_count ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* krealloc (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int expand_corename(struct core_name *cn)
{
	char *old_corename = cn->corename;

	cn->size = CORENAME_MAX_SIZE * atomic_inc_return(&call_count);
	cn->corename = krealloc(old_corename, cn->size, GFP_KERNEL);

	if (!cn->corename) {
		kfree(old_corename);
		return -ENOMEM;
	}

	return 0;
}