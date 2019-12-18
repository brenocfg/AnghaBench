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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  DBG_TRACE 128 
 int EPERM ; 
 int KDBG_EXTRACT_CLASS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kdebug_validate_debugid(uint32_t debugid)
{
	uint8_t debugid_class;

	debugid_class = KDBG_EXTRACT_CLASS(debugid);
	switch (debugid_class) {
		case DBG_TRACE:
			return EPERM;
	}

	return 0;
}