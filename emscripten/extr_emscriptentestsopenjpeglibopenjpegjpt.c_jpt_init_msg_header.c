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
struct TYPE_3__ {scalar_t__ Layer_nb; scalar_t__ Msg_length; scalar_t__ Msg_offset; scalar_t__ CSn_Id; scalar_t__ Class_Id; scalar_t__ last_byte; scalar_t__ Id; } ;
typedef  TYPE_1__ opj_jpt_msg_header_t ;

/* Variables and functions */

void jpt_init_msg_header(opj_jpt_msg_header_t * header) {
	header->Id = 0;		/* In-class Identifier    */
	header->last_byte = 0;	/* Last byte information  */
	header->Class_Id = 0;		/* Class Identifier       */
	header->CSn_Id = 0;		/* CSn : index identifier */
	header->Msg_offset = 0;	/* Message offset         */
	header->Msg_length = 0;	/* Message length         */
	header->Layer_nb = 0;		/* Auxiliary for JPP case */
}