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
struct tx_holding_buffer {unsigned int buffer_size; int /*<<< orphan*/  buffer; } ;
struct mgsl_struct {size_t tx_holding_count; size_t num_tx_holding_buffers; size_t put_tx_holding_index; struct tx_holding_buffer* tx_holding_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static int save_tx_buffer_request(struct mgsl_struct *info,const char *Buffer, unsigned int BufferSize)
{
	struct tx_holding_buffer *ptx;

	if ( info->tx_holding_count >= info->num_tx_holding_buffers ) {
		return 0;	        /* all buffers in use */
	}

	ptx = &info->tx_holding_buffers[info->put_tx_holding_index];
	ptx->buffer_size = BufferSize;
	memcpy( ptx->buffer, Buffer, BufferSize);

	++info->tx_holding_count;
	if ( ++info->put_tx_holding_index >= info->num_tx_holding_buffers)
		info->put_tx_holding_index=0;

	return 1;
}