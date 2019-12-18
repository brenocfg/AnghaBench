#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int srtp_enabled; int /*<<< orphan*/  srtp; } ;
typedef  TYPE_1__ RTPDemuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_srtp_set_crypto (int /*<<< orphan*/ *,char const*,char const*) ; 

void ff_rtp_parse_set_crypto(RTPDemuxContext *s, const char *suite,
                             const char *params)
{
    if (!ff_srtp_set_crypto(&s->srtp, suite, params))
        s->srtp_enabled = 1;
}