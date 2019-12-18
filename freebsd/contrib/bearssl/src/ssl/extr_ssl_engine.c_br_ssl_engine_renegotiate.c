#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int reneg; int flags; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 int BR_OPT_NO_RENEGOTIATION ; 
 scalar_t__ br_ssl_engine_closed (TYPE_1__*) ; 
 int /*<<< orphan*/ * br_ssl_engine_recvapp_buf (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  jump_handshake (TYPE_1__*,int) ; 

int
br_ssl_engine_renegotiate(br_ssl_engine_context *cc)
{
	size_t len;

	if (br_ssl_engine_closed(cc) || cc->reneg == 1
		|| (cc->flags & BR_OPT_NO_RENEGOTIATION) != 0
		|| br_ssl_engine_recvapp_buf(cc, &len) != NULL)
	{
		return 0;
	}
	jump_handshake(cc, 2);
	return 1;
}