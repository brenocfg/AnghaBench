#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cat; } ;
struct TYPE_5__ {TYPE_3__* level; } ;
struct user_datum {TYPE_1__ dfltlevel; TYPE_2__ range; int /*<<< orphan*/  roles; } ;
struct TYPE_6__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static int user_destroy(void *key, void *datum, void *p)
{
	struct user_datum *usrdatum;

	kfree(key);
	usrdatum = datum;
	ebitmap_destroy(&usrdatum->roles);
	ebitmap_destroy(&usrdatum->range.level[0].cat);
	ebitmap_destroy(&usrdatum->range.level[1].cat);
	ebitmap_destroy(&usrdatum->dfltlevel.cat);
	kfree(datum);
	return 0;
}