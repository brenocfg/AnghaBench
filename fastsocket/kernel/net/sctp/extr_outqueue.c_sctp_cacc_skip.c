#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ changeover_active; } ;
struct sctp_transport {TYPE_1__ cacc; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ sctp_cacc_skip_3_1 (struct sctp_transport*,struct sctp_transport*,int) ; 
 scalar_t__ sctp_cacc_skip_3_2 (struct sctp_transport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sctp_cacc_skip(struct sctp_transport *primary,
				 struct sctp_transport *transport,
				 int count_of_newacks,
				 __u32 tsn)
{
	if (primary->cacc.changeover_active &&
	    (sctp_cacc_skip_3_1(primary, transport, count_of_newacks)
	     || sctp_cacc_skip_3_2(primary, tsn)))
		return 1;
	return 0;
}