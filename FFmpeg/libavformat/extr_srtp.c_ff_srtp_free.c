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
struct SRTPContext {int /*<<< orphan*/ * hmac; int /*<<< orphan*/  aes; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_hmac_free (int /*<<< orphan*/ *) ; 

void ff_srtp_free(struct SRTPContext *s)
{
    if (!s)
        return;
    av_freep(&s->aes);
    if (s->hmac)
        av_hmac_free(s->hmac);
    s->hmac = NULL;
}