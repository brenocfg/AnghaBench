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
struct sctp_endpoint {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 

__u32 sctp_generate_tag(const struct sctp_endpoint *ep)
{
	/* I believe that this random number generator complies with RFC1750.
	 * A tag of 0 is reserved for special cases (e.g. INIT).
	 */
	__u32 x;

	do {
		get_random_bytes(&x, sizeof(__u32));
	} while (x == 0);

	return x;
}