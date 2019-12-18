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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERRCODE_QUERY_CANCELED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HOLD_CANCEL_INTERRUPTS () ; 
 int /*<<< orphan*/  RESUME_CANCEL_INTERRUPTS () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int pq_getbyte () ; 
 int pq_getmessage (int /*<<< orphan*/ ,int const) ; 
 int pq_getmsgstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_startmsgread () ; 

__attribute__((used)) static bool
ReceiveCopyData(StringInfo copyData)
{
	int messageType = 0;
	int messageCopied = 0;
	bool copyDone = true;
	const int unlimitedSize = 0;

	HOLD_CANCEL_INTERRUPTS();
	pq_startmsgread();
	messageType = pq_getbyte();
	if (messageType == EOF)
	{
		ereport(ERROR, (errcode(ERRCODE_CONNECTION_FAILURE),
						errmsg("unexpected EOF on client connection")));
	}

	/* consume the rest of message before checking for message type */
	messageCopied = pq_getmessage(copyData, unlimitedSize);
	if (messageCopied == EOF)
	{
		ereport(ERROR, (errcode(ERRCODE_CONNECTION_FAILURE),
						errmsg("unexpected EOF on client connection")));
	}

	RESUME_CANCEL_INTERRUPTS();

	switch (messageType)
	{
		case 'd':       /* CopyData */
		{
			copyDone = false;
			break;
		}

		case 'c':       /* CopyDone */
		{
			copyDone = true;
			break;
		}

		case 'f':       /* CopyFail */
		{
			ereport(ERROR, (errcode(ERRCODE_QUERY_CANCELED),
							errmsg("COPY data failed: %s", pq_getmsgstring(copyData))));
			break;
		}

		case 'H':       /* Flush */
		case 'S':       /* Sync */
		{
			/*
			 * Ignore Flush/Sync for the convenience of client libraries (such
			 * as libpq) that may send those without noticing that the command
			 * they just sent was COPY.
			 */
			copyDone = false;
			break;
		}

		default:
		{
			ereport(ERROR, (errcode(ERRCODE_PROTOCOL_VIOLATION),
							errmsg("unexpected message type 0x%02X during COPY data",
								   messageType)));
			break;
		}
	}

	return copyDone;
}