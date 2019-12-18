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
struct pri_detector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pri_detector*) ; 
 int /*<<< orphan*/  pool_deregister_ref () ; 
 int /*<<< orphan*/  pri_detector_reset (struct pri_detector*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pri_detector_exit(struct pri_detector *de)
{
	pri_detector_reset(de, 0);
	pool_deregister_ref();
	kfree(de);
}