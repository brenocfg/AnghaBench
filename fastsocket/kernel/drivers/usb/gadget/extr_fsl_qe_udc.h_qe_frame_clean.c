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
struct qe_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_OK ; 
 int /*<<< orphan*/  frame_set_data (struct qe_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_set_info (struct qe_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_set_length (struct qe_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_set_privdata (struct qe_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_set_status (struct qe_frame*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qe_frame_clean(struct qe_frame *frm)
{
	frame_set_data(frm, NULL);
	frame_set_length(frm, 0);
	frame_set_status(frm, FRAME_OK);
	frame_set_info(frm, 0);
	frame_set_privdata(frm, NULL);
}