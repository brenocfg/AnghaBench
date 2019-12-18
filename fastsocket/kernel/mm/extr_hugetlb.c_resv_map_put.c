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
struct vm_area_struct {int dummy; } ;
struct resv_map {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resv_map_release ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static void resv_map_put(struct vm_area_struct *vma)
{
	struct resv_map *reservations = vma_resv_map(vma);

	if (!reservations)
		return;
	kref_put(&reservations->refs, resv_map_release);
}