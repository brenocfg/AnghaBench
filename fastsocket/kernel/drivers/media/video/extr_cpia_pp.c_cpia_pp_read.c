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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct parport {TYPE_1__ ieee1284; } ;

/* Variables and functions */
 scalar_t__ IEEE1284_MODE_NIBBLE ; 
 int cpia_read_nibble_stream (struct parport*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int parport_read (struct parport*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cpia_pp_read(struct parport *port, u8 *buffer, int len)
{
	int bytes_read;

	/* support for CPiA variant "nibble stream" reads */
	if(port->ieee1284.mode == IEEE1284_MODE_NIBBLE)
		bytes_read = cpia_read_nibble_stream(port,buffer,len,0);
	else {
		int new_bytes;
		for(bytes_read=0; bytes_read<len; bytes_read += new_bytes) {
			new_bytes = parport_read(port, buffer+bytes_read,
						 len-bytes_read);
			if(new_bytes < 0) break;
		}
	}
	return bytes_read;
}