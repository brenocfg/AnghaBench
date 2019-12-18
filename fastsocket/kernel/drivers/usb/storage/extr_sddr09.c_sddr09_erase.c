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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 unsigned char LSB_of (unsigned long) ; 
 unsigned char LUNBITS ; 
 unsigned char MSB_of (unsigned long) ; 
 int /*<<< orphan*/  US_DEBUGP (char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sddr09_send_scsi_command (struct us_data*,unsigned char*,int) ; 

__attribute__((used)) static int
sddr09_erase(struct us_data *us, unsigned long Eaddress) {
	unsigned char *command = us->iobuf;
	int result;

	US_DEBUGP("sddr09_erase: erase address %lu\n", Eaddress);

	memset(command, 0, 12);
	command[0] = 0xEA;
	command[1] = LUNBITS;
	command[6] = MSB_of(Eaddress>>16);
	command[7] = LSB_of(Eaddress>>16);
	command[8] = MSB_of(Eaddress & 0xFFFF);
	command[9] = LSB_of(Eaddress & 0xFFFF);

	result = sddr09_send_scsi_command(us, command, 12);

	if (result)
		US_DEBUGP("Result for send_control in sddr09_erase %d\n",
			  result);

	return result;
}