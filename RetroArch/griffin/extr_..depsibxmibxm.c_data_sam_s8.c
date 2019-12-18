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
struct data {int length; char* buffer; } ;

/* Variables and functions */

__attribute__((used)) static void data_sam_s8( struct data *data, int offset, int count, short *dest ) {
	int idx, amp, length = data->length;
	char *buffer = data->buffer;
	if( offset > length ) {
		offset = length;
	}
	if( offset + count > length ) {
		count = length - offset;
	}
	for( idx = 0; idx < count; idx++ ) {
		amp = ( buffer[ offset + idx ] & 0xFF ) << 8;
		dest[ idx ] = ( amp & 0x7FFF ) - ( amp & 0x8000 );
	}
}