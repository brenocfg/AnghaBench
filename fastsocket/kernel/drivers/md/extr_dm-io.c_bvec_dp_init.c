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
struct dpages {struct bio_vec* context_ptr; int /*<<< orphan*/  next_page; int /*<<< orphan*/  get_page; } ;
struct bio_vec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bvec_get_page ; 
 int /*<<< orphan*/  bvec_next_page ; 

__attribute__((used)) static void bvec_dp_init(struct dpages *dp, struct bio_vec *bvec)
{
	dp->get_page = bvec_get_page;
	dp->next_page = bvec_next_page;
	dp->context_ptr = bvec;
}