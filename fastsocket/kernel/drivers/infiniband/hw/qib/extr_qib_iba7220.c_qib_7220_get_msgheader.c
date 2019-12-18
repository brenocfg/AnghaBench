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
typedef  int u32 ;
struct qib_message_header {int dummy; } ;
struct qib_devdata {int /*<<< orphan*/ * rhf_offset; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int qib_hdrget_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qib_message_header *
qib_7220_get_msgheader(struct qib_devdata *dd, __le32 *rhf_addr)
{
	u32 offset = qib_hdrget_offset(rhf_addr);

	return (struct qib_message_header *)
		(rhf_addr - dd->rhf_offset + offset);
}