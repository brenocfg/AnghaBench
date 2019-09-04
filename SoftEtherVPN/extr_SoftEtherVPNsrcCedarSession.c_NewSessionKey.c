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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rand32 () ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

void NewSessionKey(CEDAR *cedar, UCHAR *session_key, UINT *session_key_32)
{
	// Validate arguments
	if (cedar == NULL || session_key == NULL || session_key_32 == NULL)
	{
		return;
	}

	Rand(session_key, SHA1_SIZE);
	*session_key_32 = Rand32();
}