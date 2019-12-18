#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* gr; scalar_t__ emu_status; } ;
typedef  TYPE_2__ ssp1601_t ;
struct TYPE_5__ {int v; } ;

/* Variables and functions */
 size_t SSP_GR0 ; 
 int rPC ; 
 scalar_t__ rST ; 
 scalar_t__ rSTACK ; 
 TYPE_2__* ssp ; 

void ssp1601_reset(ssp1601_t *l_ssp)
{
	ssp = l_ssp;
	ssp->emu_status = 0;
	ssp->gr[SSP_GR0].v = 0xffff0000;
	rPC = 0x400;
	rSTACK = 0; // ? using ascending stack
	rST = 0;
}