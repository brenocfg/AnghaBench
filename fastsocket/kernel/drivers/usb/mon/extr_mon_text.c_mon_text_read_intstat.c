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
struct mon_text_ptr {scalar_t__ cnt; scalar_t__ limit; scalar_t__ pbuf; } ;
struct mon_reader_text {int dummy; } ;
struct mon_event_text {int status; int interval; } ;

/* Variables and functions */
 scalar_t__ snprintf (scalar_t__,scalar_t__,char*,int,int) ; 

__attribute__((used)) static void mon_text_read_intstat(struct mon_reader_text *rp,
	struct mon_text_ptr *p, const struct mon_event_text *ep)
{
	p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
	    " %d:%d", ep->status, ep->interval);
}