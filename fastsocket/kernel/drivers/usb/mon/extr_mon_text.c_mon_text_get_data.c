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
struct mon_event_text {int /*<<< orphan*/  data; scalar_t__ is_in; } ;
struct mon_bus {int dummy; } ;

/* Variables and functions */
 int DATA_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline char mon_text_get_data(struct mon_event_text *ep, struct urb *urb,
    int len, char ev_type, struct mon_bus *mbus)
{
	if (len <= 0)
		return 'L';
	if (len >= DATA_MAX)
		len = DATA_MAX;

	if (ep->is_in) {
		if (ev_type != 'C')
			return '<';
	} else {
		if (ev_type != 'S')
			return '>';
	}

	if (urb->transfer_buffer == NULL)
		return 'Z';	/* '0' would be not as pretty. */

	memcpy(ep->data, urb->transfer_buffer, len);
	return 0;
}