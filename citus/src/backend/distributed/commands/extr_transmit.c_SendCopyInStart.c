#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pq_beginmessage (TYPE_1__*,char) ; 
 int /*<<< orphan*/  pq_endmessage (TYPE_1__*) ; 
 int pq_flush () ; 
 int /*<<< orphan*/  pq_sendbyte (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  pq_sendint (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SendCopyInStart(void)
{
	StringInfoData copyInStart = { NULL, 0, 0, 0 };
	const char copyFormat = 1; /* binary copy format */
	int flushed = 0;

	pq_beginmessage(&copyInStart, 'G');
	pq_sendbyte(&copyInStart, copyFormat);
	pq_sendint(&copyInStart, 0, 2);
	pq_endmessage(&copyInStart);

	/* flush here to ensure that FE knows it can send data */
	flushed = pq_flush();
	if (flushed != 0)
	{
		ereport(WARNING, (errmsg("could not flush copy start data")));
	}
}