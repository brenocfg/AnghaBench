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
typedef  int /*<<< orphan*/  alist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIST_HASH_SIZE ; 
 int /*<<< orphan*/  alist_cmp ; 
 int /*<<< orphan*/  alist_hash ; 
 int /*<<< orphan*/ * alist_xnew (int /*<<< orphan*/ ,void (*) (void*),void (*) (void*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

alist_t *
alist_new(void (*namefree)(void *), void (*valfree)(void *))
{
	return (alist_xnew(ALIST_HASH_SIZE, namefree, valfree,
	    alist_hash, alist_cmp));
}