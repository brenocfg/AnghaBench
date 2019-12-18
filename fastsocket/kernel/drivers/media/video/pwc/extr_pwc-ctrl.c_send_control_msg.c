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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pwc_device {int /*<<< orphan*/  vcinterface; } ;

/* Variables and functions */
 int _send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static inline int send_control_msg(struct pwc_device *pdev,
	u8 request, u16 value, void *buf, int buflen)
{
	return _send_control_msg(pdev,
		request, value, pdev->vcinterface, buf, buflen, 500);
}