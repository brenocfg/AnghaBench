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
struct secpolicy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  M_SECA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sadb_mutex ; 

struct secpolicy *
keydb_newsecpolicy(void)
{
	struct secpolicy *p;

	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_NOTOWNED);

	return (struct secpolicy *)_MALLOC(sizeof(*p), M_SECA,
	    M_WAITOK | M_ZERO);
}