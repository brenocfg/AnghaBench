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
struct iscsi_conn {TYPE_1__* session; } ;
typedef  scalar_t__ itt_t ;
struct TYPE_2__ {int age; } ;

/* Variables and functions */

__attribute__((used)) static void beiscsi_parse_pdu(struct iscsi_conn *conn, itt_t itt,
			      int *index, int *age)
{
	*index = (int)itt;
	if (age)
		*age = conn->session->age;
}