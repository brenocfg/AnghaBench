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
struct inode {int dummy; } ;
struct ima_iint_cache {int /*<<< orphan*/  writecount; int /*<<< orphan*/  readcount; } ;
typedef  enum iint_pcr_error { ____Placeholder_iint_pcr_error } iint_pcr_error ;

/* Variables and functions */
#define  OPEN_WRITERS 129 
#define  TOMTOU 128 
 int /*<<< orphan*/  ima_add_violation (struct inode*,unsigned char const*,char*,char*) ; 

__attribute__((used)) static void ima_read_write_check(enum iint_pcr_error error,
				 struct ima_iint_cache *iint,
				 struct inode *inode,
				 const unsigned char *filename)
{
	switch (error) {
	case TOMTOU:
		if (iint->readcount > 0)
			ima_add_violation(inode, filename, "invalid_pcr",
					  "ToMToU");
		break;
	case OPEN_WRITERS:
		if (iint->writecount > 0)
			ima_add_violation(inode, filename, "invalid_pcr",
					  "open_writers");
		break;
	}
}