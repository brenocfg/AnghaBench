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
struct resource {int /*<<< orphan*/  start; } ;
struct expansion_card {int slot_no; int /*<<< orphan*/  loader; struct resource* resource; scalar_t__ easi; } ;
struct ecard_request {struct expansion_card* ec; } ;

/* Variables and functions */
 size_t ECARD_RES_EASI ; 
 size_t ECARD_RES_IOCSYNC ; 
 size_t ECARD_RES_MEMC ; 
 int /*<<< orphan*/  ecard_loader_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecard_task_reset(struct ecard_request *req)
{
	struct expansion_card *ec = req->ec;
	struct resource *res;

	res = ec->slot_no == 8
		? &ec->resource[ECARD_RES_MEMC]
		: ec->easi
		  ? &ec->resource[ECARD_RES_EASI]
		  : &ec->resource[ECARD_RES_IOCSYNC];

	ecard_loader_reset(res->start, ec->loader);
}