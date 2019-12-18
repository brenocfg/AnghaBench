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
struct ehci_hcd {int dummy; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SHORT_READ (int) ; 
 int QTD_STS_ACTIVE ; 
 int QTD_STS_HALT ; 
 int hc32_to_cpu (struct ehci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char token_mark(struct ehci_hcd *ehci, __hc32 token)
{
	__u32 v = hc32_to_cpu(ehci, token);

	if (v & QTD_STS_ACTIVE)
		return '*';
	if (v & QTD_STS_HALT)
		return '-';
	if (!IS_SHORT_READ (v))
		return ' ';
	/* tries to advance through hw_alt_next */
	return '/';
}