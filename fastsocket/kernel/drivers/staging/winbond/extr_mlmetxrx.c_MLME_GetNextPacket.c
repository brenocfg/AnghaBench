#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  DataType; scalar_t__ len; int /*<<< orphan*/  pMMPDU; } ;
struct wbsoft_priv {TYPE_1__ sMlmeFrame; } ;
struct wb35_descriptor {size_t InternalUsed; size_t buffer_start_index; size_t buffer_number; int /*<<< orphan*/  Type; int /*<<< orphan*/  buffer_total_size; scalar_t__* buffer_size; int /*<<< orphan*/ * buffer_address; } ;

/* Variables and functions */
 size_t MAX_DESCRIPTOR_BUFFER_INDEX ; 

void MLME_GetNextPacket(struct wbsoft_priv *adapter, struct wb35_descriptor *desc)
{
	desc->InternalUsed = desc->buffer_start_index + desc->buffer_number;
	desc->InternalUsed %= MAX_DESCRIPTOR_BUFFER_INDEX;
	desc->buffer_address[desc->InternalUsed] = adapter->sMlmeFrame.pMMPDU;
	desc->buffer_size[desc->InternalUsed] = adapter->sMlmeFrame.len;
	desc->buffer_total_size += adapter->sMlmeFrame.len;
	desc->buffer_number++;
	desc->Type = adapter->sMlmeFrame.DataType;
}