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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  CopyConnectionState ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
ConnectionStateList(HTAB *connectionStateHash)
{
	List *connectionStateList = NIL;
	HASH_SEQ_STATUS status;
	CopyConnectionState *connectionState = NULL;

	hash_seq_init(&status, connectionStateHash);

	connectionState = (CopyConnectionState *) hash_seq_search(&status);
	while (connectionState != NULL)
	{
		connectionStateList = lappend(connectionStateList, connectionState);

		connectionState = (CopyConnectionState *) hash_seq_search(&status);
	}

	return connectionStateList;
}