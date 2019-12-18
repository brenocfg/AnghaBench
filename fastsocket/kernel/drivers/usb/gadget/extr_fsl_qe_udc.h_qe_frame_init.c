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
struct qe_frame {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qe_frame_clean (struct qe_frame*) ; 

__attribute__((used)) static inline void qe_frame_init(struct qe_frame *frm)
{
	qe_frame_clean(frm);
	INIT_LIST_HEAD(&(frm->node));
}