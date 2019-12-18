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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 struct mm_struct* allocate_mm () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (struct mm_struct*,int /*<<< orphan*/ ,int) ; 
 struct mm_struct* mm_init (struct mm_struct*,int /*<<< orphan*/ ) ; 

struct mm_struct * mm_alloc(void)
{
	struct mm_struct * mm;

	mm = allocate_mm();
	if (mm) {
		memset(mm, 0, sizeof(*mm));
		mm = mm_init(mm, current);
	}
	return mm;
}