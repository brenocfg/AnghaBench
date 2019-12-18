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
struct sockaddr {int dummy; } ;
struct TCP_Server_Info {int /*<<< orphan*/  response_q; int /*<<< orphan*/  dstaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_PORT ; 
#define  RFC1002_NEGATIVE_SESSION_RESPONSE 131 
#define  RFC1002_POSITIVE_SESSION_RESPONSE 130 
#define  RFC1002_SESSION_KEEP_ALIVE 129 
#define  RFC1002_SESSION_MESSAGE 128 
 int /*<<< orphan*/  cERROR (int,char*,unsigned char) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  cifs_reconnect (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_set_port (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
is_smb_response(struct TCP_Server_Info *server, unsigned char type)
{
	/*
	 * The first byte big endian of the length field,
	 * is actually not part of the length but the type
	 * with the most common, zero, as regular data.
	 */
	switch (type) {
	case RFC1002_SESSION_MESSAGE:
		/* Regular SMB response */
		return true;
	case RFC1002_SESSION_KEEP_ALIVE:
		cFYI(1, "RFC 1002 session keep alive");
		break;
	case RFC1002_POSITIVE_SESSION_RESPONSE:
		cFYI(1, "RFC 1002 positive session response");
		break;
	case RFC1002_NEGATIVE_SESSION_RESPONSE:
		/*
		 * We get this from Windows 98 instead of an error on
		 * SMB negprot response.
		 */
		cFYI(1, "RFC 1002 negative session response");
		/* give server a second to clean up */
		msleep(1000);
		/*
		 * Always try 445 first on reconnect since we get NACK
		 * on some if we ever connected to port 139 (the NACK
		 * is since we do not begin with RFC1001 session
		 * initialize frame).
		 */
		cifs_set_port((struct sockaddr *)&server->dstaddr, CIFS_PORT);
		cifs_reconnect(server);
		wake_up(&server->response_q);
		break;
	default:
		cERROR(1, "RFC 1002 unknown response type 0x%x", type);
		cifs_reconnect(server);
	}

	return false;
}