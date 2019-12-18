#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  fec_hd; int /*<<< orphan*/  rtcp_hd; int /*<<< orphan*/  rtp_hd; int /*<<< orphan*/  filters; } ;
typedef  TYPE_2__ RTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_ip_reset_filters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_closep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtp_close(URLContext *h)
{
    RTPContext *s = h->priv_data;

    ff_ip_reset_filters(&s->filters);

    ffurl_close(s->rtp_hd);
    ffurl_close(s->rtcp_hd);
    ffurl_closep(&s->fec_hd);
    return 0;
}