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
struct uwb_rceb {scalar_t__ bEventType; scalar_t__ wEvent; scalar_t__ bEventContext; } ;
struct uwb_rc_neh {scalar_t__ evt_type; scalar_t__ evt; scalar_t__ context; } ;

/* Variables and functions */

__attribute__((used)) static bool uwb_rc_neh_match(struct uwb_rc_neh *neh, const struct uwb_rceb *rceb)
{
	return neh->evt_type == rceb->bEventType
		&& neh->evt == rceb->wEvent
		&& neh->context == rceb->bEventContext;
}