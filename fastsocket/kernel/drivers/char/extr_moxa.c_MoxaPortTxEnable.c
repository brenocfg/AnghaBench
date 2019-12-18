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
struct moxa_port {int /*<<< orphan*/  tableAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_SetXonState ; 
 int /*<<< orphan*/  Magic_code ; 
 int /*<<< orphan*/  moxafunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MoxaPortTxEnable(struct moxa_port *port)
{
	moxafunc(port->tableAddr, FC_SetXonState, Magic_code);
}