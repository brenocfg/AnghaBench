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
typedef  int /*<<< orphan*/  i2eBordStrPtr ;

/* Variables and functions */
 int /*<<< orphan*/  iiSendPendingMail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iiSendPendingMail_t(unsigned long data)
{
	i2eBordStrPtr pB = (i2eBordStrPtr)data;

	iiSendPendingMail(pB);
}