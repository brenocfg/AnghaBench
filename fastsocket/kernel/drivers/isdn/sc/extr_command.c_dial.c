#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phone; } ;
typedef  TYPE_1__ setup_parm ;
struct TYPE_5__ {int /*<<< orphan*/  devicename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  ceReqClass1 ; 
 int /*<<< orphan*/  ceReqPhyConnect ; 
 int /*<<< orphan*/  ceReqTypePhy ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_2__** sc_adapter ; 
 int sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int dial(int card, unsigned long channel, setup_parm setup)
{
	int status;
	char Phone[48];
  
	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	/*extract ISDN number to dial from eaz/msn string*/ 
	strcpy(Phone,setup.phone); 

	/*send the connection message*/
	status = sendmessage(card, CEPID,ceReqTypePhy,
				ceReqClass1,
				ceReqPhyConnect,
				(unsigned char) channel+1, 
				strlen(Phone),
				(unsigned int *) Phone);

	pr_debug("%s: Dialing %s on channel %lu\n",
		sc_adapter[card]->devicename, Phone, channel+1);
	
	return status;
}