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
struct data {int length; int* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static char* data_ascii( struct data *data, int offset, int length, char *dest ) {
	int idx, chr;
	memset( dest, 32, length );
	if( offset > data->length ) {
		offset = data->length;
	}
	if( ( unsigned int ) offset + length > ( unsigned int ) data->length ) {
		length = data->length - offset;
	}
	for( idx = 0; idx < length; idx++ ) {
		chr = data->buffer[ offset + idx ] & 0xFF;
		if( chr > 32 ) {
			dest[ idx ] = chr;
		}
	}
	return dest;
}