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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

PACK *PackAdditionalConnect(UCHAR *session_key)
{
	PACK *p;
	// Validate arguments
	if (session_key == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "method", "additional_connect");
	PackAddData(p, "session_key", session_key, SHA1_SIZE);

	return p;
}