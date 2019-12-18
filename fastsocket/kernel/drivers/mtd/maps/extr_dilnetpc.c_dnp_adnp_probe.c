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
 int /*<<< orphan*/  BIOSID_BASE ; 
 int /*<<< orphan*/  ID_ADNP ; 
 int /*<<< orphan*/  ID_DNPC ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnp_adnp_probe(void)
{
	char *biosid, rc = -1;

	biosid = (char*)ioremap(BIOSID_BASE, 16);
	if(biosid)
	{
		if(!strcmp(biosid, ID_DNPC))
			rc = 1;		/* this is a DNPC  */
		else if(!strcmp(biosid, ID_ADNP))
			rc = 0;		/* this is a ADNPC */
	}
	iounmap((void *)biosid);
	return(rc);
}