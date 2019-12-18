#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  io; } ;
struct TYPE_14__ {int /*<<< orphan*/ * RBuffer; } ;
struct TYPE_13__ {int /*<<< orphan*/  P; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  P; } ;
struct TYPE_12__ {TYPE_1__ RBuffer; } ;
typedef  TYPE_2__* PISDN_ADAPTER ;
typedef  TYPE_3__ PBUFFER ;
typedef  TYPE_4__ ENTITY ;
typedef  int /*<<< orphan*/  DBUFFER ;
typedef  TYPE_5__ ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  mem_in_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_inw (TYPE_5__*,int /*<<< orphan*/ *) ; 

void mem_look_ahead (ADAPTER *a, PBUFFER *RBuffer, ENTITY *e)
{
 PISDN_ADAPTER IoAdapter = (PISDN_ADAPTER)a->io ;
 IoAdapter->RBuffer.length = mem_inw (a, &RBuffer->length) ;
 mem_in_buffer (a, RBuffer->P, IoAdapter->RBuffer.P,
                IoAdapter->RBuffer.length) ;
 e->RBuffer = (DBUFFER *)&IoAdapter->RBuffer ;
}