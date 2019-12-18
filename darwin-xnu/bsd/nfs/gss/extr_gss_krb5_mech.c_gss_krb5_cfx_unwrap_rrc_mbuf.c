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
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  gss_cfx_wrap_token_desc ;

/* Variables and functions */
 int /*<<< orphan*/  gss_join_mbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_normalize_mbuf (int /*<<< orphan*/ ,int,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gss_krb5_cfx_unwrap_rrc_mbuf(mbuf_t header, size_t rrc)
{
	mbuf_t body, trailer;

	gss_normalize_mbuf(header, sizeof(gss_cfx_wrap_token_desc), &rrc, &trailer, &body, 0);
	gss_join_mbuf(header, body, trailer);
}