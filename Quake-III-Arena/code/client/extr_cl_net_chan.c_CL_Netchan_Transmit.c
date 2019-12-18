#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netchan_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cursize; } ;
typedef  TYPE_1__ msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_Netchan_Encode (TYPE_1__*) ; 
 int /*<<< orphan*/  MSG_WriteByte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Netchan_Transmit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clc_EOF ; 

void CL_Netchan_Transmit( netchan_t *chan, msg_t* msg ) {
	MSG_WriteByte( msg, clc_EOF );

	CL_Netchan_Encode( msg );
	Netchan_Transmit( chan, msg->cursize, msg->data );
}