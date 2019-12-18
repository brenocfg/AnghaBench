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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CODELENGTH (unsigned int,unsigned char*) ; 
 int MINISSDPC_INVALID_INPUT ; 
 int MINISSDPC_SOCKET_ERROR ; 
 int MINISSDPC_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ write (int,unsigned char*,int) ; 

int
requestDevicesFromMiniSSDPD(int s, const char * devtype)
{
	unsigned char buffer[256];
	unsigned char * p;
	unsigned int l;
	unsigned stsize = (unsigned)strlen(devtype);
	if(stsize == 8 && 0 == memcmp(devtype, "ssdp:all", 8))
	{
		buffer[0] = 3;	/* request type 3 : everything */
	}
	else
	{
		buffer[0] = 1; /* request type 1 : request devices/services by type */
	}
	p = buffer + 1;
	l = stsize;	CODELENGTH(l, p);
	if(p + stsize > buffer + sizeof(buffer))
	{
		/* devtype is too long ! */
#ifdef DEBUG
		fprintf(stderr, "devtype is too long ! stsize=%u sizeof(buffer)=%u\n",
		        stsize, (unsigned)sizeof(buffer));
#endif /* DEBUG */
		return MINISSDPC_INVALID_INPUT;
	}
	memcpy(p, devtype, stsize);
	p += stsize;
	if(write(s, buffer, p - buffer) < 0)
	{
		/*syslog(LOG_ERR, "write(): %m");*/
		perror("minissdpc.c: write()");
		return MINISSDPC_SOCKET_ERROR;
	}
	return MINISSDPC_SUCCESS;
}