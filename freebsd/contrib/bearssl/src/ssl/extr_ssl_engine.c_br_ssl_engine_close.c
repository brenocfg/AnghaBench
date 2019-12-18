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
typedef  int /*<<< orphan*/  br_ssl_engine_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_ssl_engine_closed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jump_handshake (int /*<<< orphan*/ *,int) ; 

void
br_ssl_engine_close(br_ssl_engine_context *cc)
{
	if (!br_ssl_engine_closed(cc)) {
		jump_handshake(cc, 1);
	}
}