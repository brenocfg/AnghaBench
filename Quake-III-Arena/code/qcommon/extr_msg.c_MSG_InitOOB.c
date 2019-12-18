#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int maxsize; int /*<<< orphan*/  oob; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ msg_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSG_initHuffman () ; 
 int /*<<< orphan*/  msgInit ; 
 int /*<<< orphan*/  qtrue ; 

void MSG_InitOOB( msg_t *buf, byte *data, int length ) {
	if (!msgInit) {
		MSG_initHuffman();
	}
	Com_Memset (buf, 0, sizeof(*buf));
	buf->data = data;
	buf->maxsize = length;
	buf->oob = qtrue;
}