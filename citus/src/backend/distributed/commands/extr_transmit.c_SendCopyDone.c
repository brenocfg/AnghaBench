#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pq_beginmessage (TYPE_1__*,char) ; 
 int /*<<< orphan*/  pq_endmessage (TYPE_1__*) ; 
 int pq_flush () ; 

__attribute__((used)) static void
SendCopyDone(void)
{
	StringInfoData copyDone = { NULL, 0, 0, 0 };
	int flushed = 0;

	pq_beginmessage(&copyDone, 'c');
	pq_endmessage(&copyDone);

	/* flush here to signal to FE that we are done */
	flushed = pq_flush();
	if (flushed != 0)
	{
		ereport(WARNING, (errmsg("could not flush copy start data")));
	}
}