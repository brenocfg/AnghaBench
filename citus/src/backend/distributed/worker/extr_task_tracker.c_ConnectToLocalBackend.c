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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 char* LOCAL_HOST_NAME ; 
 int /*<<< orphan*/  MultiClientConnect (char const*,int /*<<< orphan*/  const,char const*,char const*) ; 
 int /*<<< orphan*/  PostPortNumber ; 

__attribute__((used)) static int32
ConnectToLocalBackend(const char *databaseName, const char *userName)
{
	const char *nodeName = LOCAL_HOST_NAME;
	const uint32 nodePort = PostPortNumber;

	/*
	 * Our client library currently only handles TCP sockets. We therefore do
	 * not use Unix domain sockets here.
	 */
	int32 connectionId = MultiClientConnect(nodeName, nodePort, databaseName, userName);

	return connectionId;
}