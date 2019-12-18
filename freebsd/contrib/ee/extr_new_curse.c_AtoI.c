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
 char* TERM_data_ptr ; 

int 
AtoI()		/* convert ascii text to integers	*/
{
	int Temp;

	Temp = 0;
	while ((*TERM_data_ptr >= '0') && (*TERM_data_ptr <= '9'))
	{
		Temp = (Temp * 10) + (*TERM_data_ptr - '0');
		TERM_data_ptr++;
	}
	return(Temp);
}