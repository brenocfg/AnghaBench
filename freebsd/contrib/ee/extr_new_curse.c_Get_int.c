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

/* Variables and functions */
 scalar_t__ Flip_Bytes ; 
 int /*<<< orphan*/  TERM_data_ptr ; 

int 
Get_int()		/* get a two-byte integer from the terminfo file */
{
	int High_byte;
	int Low_byte;
	int temp;

	Low_byte = *((unsigned char *) TERM_data_ptr++);
	High_byte = *((unsigned char *) TERM_data_ptr++);
	if (Flip_Bytes)
	{
		temp = Low_byte;
		Low_byte = High_byte;
		High_byte = temp;
	}
	if ((High_byte == 255) && (Low_byte == 255))
		return (-1);
	else
		return(Low_byte + (High_byte * 256));
}