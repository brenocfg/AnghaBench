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
struct urb {int /*<<< orphan*/ * transfer_buffer; } ;
struct mon_reader_bin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mon_copy_to_buff (struct mon_reader_bin const*,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static char mon_bin_get_data(const struct mon_reader_bin *rp,
    unsigned int offset, struct urb *urb, unsigned int length)
{

	if (urb->transfer_buffer == NULL)
		return 'Z';
	mon_copy_to_buff(rp, offset, urb->transfer_buffer, length);
	return 0;
}