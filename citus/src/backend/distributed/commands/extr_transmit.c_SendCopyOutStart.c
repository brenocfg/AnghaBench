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
 int /*<<< orphan*/  pq_beginmessage (TYPE_1__*,char) ; 
 int /*<<< orphan*/  pq_endmessage (TYPE_1__*) ; 
 int /*<<< orphan*/  pq_sendbyte (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  pq_sendint (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SendCopyOutStart(void)
{
	StringInfoData copyOutStart = { NULL, 0, 0, 0 };
	const char copyFormat = 1; /* binary copy format */

	pq_beginmessage(&copyOutStart, 'H');
	pq_sendbyte(&copyOutStart, copyFormat);
	pq_sendint(&copyOutStart, 0, 2);
	pq_endmessage(&copyOutStart);
}