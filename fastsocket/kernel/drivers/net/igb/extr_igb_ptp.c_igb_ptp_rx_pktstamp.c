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
struct sk_buff {int dummy; } ;
struct igb_q_vector {int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  igb_ptp_systim_to_hwtstamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 

void igb_ptp_rx_pktstamp(struct igb_q_vector *q_vector,
			 unsigned char *va,
			 struct sk_buff *skb)
{
	__le64 *regval = (__le64 *)va;

	/* The timestamp is recorded in little endian format.
	 * DWORD: 0        1        2        3
	 * Field: Reserved Reserved SYSTIML  SYSTIMH
	 */
	igb_ptp_systim_to_hwtstamp(q_vector->adapter, skb_hwtstamps(skb),
				   le64_to_cpu(regval[1]));
}