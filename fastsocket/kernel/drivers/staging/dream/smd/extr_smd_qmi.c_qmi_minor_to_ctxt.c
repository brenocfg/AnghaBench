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
struct TYPE_2__ {unsigned int minor; } ;
struct qmi_ctxt {TYPE_1__ misc; } ;

/* Variables and functions */
 struct qmi_ctxt qmi_device0 ; 
 struct qmi_ctxt qmi_device1 ; 
 struct qmi_ctxt qmi_device2 ; 

__attribute__((used)) static struct qmi_ctxt *qmi_minor_to_ctxt(unsigned n)
{
	if (n == qmi_device0.misc.minor)
		return &qmi_device0;
	if (n == qmi_device1.misc.minor)
		return &qmi_device1;
	if (n == qmi_device2.misc.minor)
		return &qmi_device2;
	return 0;
}