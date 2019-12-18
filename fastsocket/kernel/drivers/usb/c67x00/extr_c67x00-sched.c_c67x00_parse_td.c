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
struct c67x00_td {struct c67x00_td* data; int /*<<< orphan*/  pipe; int /*<<< orphan*/  td_addr; } ;
struct c67x00_hcd {TYPE_1__* sie; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CY_TD_SIZE ; 
 int /*<<< orphan*/  c67x00_ll_read_mem_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct c67x00_td*,scalar_t__) ; 
 scalar_t__ td_actual_bytes (struct c67x00_td*) ; 
 int /*<<< orphan*/  td_ly_base_addr (struct c67x00_td*) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
c67x00_parse_td(struct c67x00_hcd *c67x00, struct c67x00_td *td)
{
	c67x00_ll_read_mem_le16(c67x00->sie->dev,
				td->td_addr, td, CY_TD_SIZE);

	if (usb_pipein(td->pipe) && td_actual_bytes(td))
		c67x00_ll_read_mem_le16(c67x00->sie->dev, td_ly_base_addr(td),
					td->data, td_actual_bytes(td));
}