#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {char* hostname; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char*) ; 
 int /*<<< orphan*/  CitusNoticeLogLevel ; 
 char* TrimLogLevel (char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
DefaultCitusNoticeProcessor(void *arg, const char *message)
{
	MultiConnection *connection = (MultiConnection *) arg;
	char *nodeName = connection->hostname;
	uint32 nodePort = connection->port;
	char *trimmedMessage = TrimLogLevel(message);
	char *level = strtok((char *) message, ":");

	ereport(CitusNoticeLogLevel,
			(errmsg("%s", ApplyLogRedaction(trimmedMessage)),
			 errdetail("%s from %s:%d", level, nodeName, nodePort)));
}