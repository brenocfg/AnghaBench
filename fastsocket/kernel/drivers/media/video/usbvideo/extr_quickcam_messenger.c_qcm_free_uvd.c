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
struct uvd {scalar_t__ user_data; } ;
struct qcm {int /*<<< orphan*/  scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_free_int (struct qcm*) ; 
 int /*<<< orphan*/  qcm_unregister_input (struct qcm*) ; 

__attribute__((used)) static void qcm_free_uvd(struct uvd *uvd)
{
	struct qcm *cam = (struct qcm *) uvd->user_data;

	kfree(cam->scratch);
	qcm_unregister_input(cam);
	qcm_free_int(cam);
}