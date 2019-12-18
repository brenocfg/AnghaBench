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
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_fcp_can_queue_ramp_down (struct fc_lport*) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,size_t) ; 
 scalar_t__ likely (struct fc_frame*) ; 

__attribute__((used)) static inline struct fc_frame *fc_fcp_frame_alloc(struct fc_lport *lport,
						  size_t len)
{
	struct fc_frame *fp;

	fp = fc_frame_alloc(lport, len);
	if (likely(fp))
		return fp;

	/* error case */
	fc_fcp_can_queue_ramp_down(lport);
	return NULL;
}