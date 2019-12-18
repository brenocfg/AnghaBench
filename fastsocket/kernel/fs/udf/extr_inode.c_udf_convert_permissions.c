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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct fileEntry {TYPE_1__ icbTag; int /*<<< orphan*/  permissions; } ;
typedef  int permissions ;
typedef  int mode_t ;

/* Variables and functions */
 int ICBTAG_FLAG_SETGID ; 
 int ICBTAG_FLAG_SETUID ; 
 int ICBTAG_FLAG_STICKY ; 
 int S_IRWXG ; 
 int /*<<< orphan*/  S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mode_t udf_convert_permissions(struct fileEntry *fe)
{
	mode_t mode;
	uint32_t permissions;
	uint32_t flags;

	permissions = le32_to_cpu(fe->permissions);
	flags = le16_to_cpu(fe->icbTag.flags);

	mode =	((permissions) & S_IRWXO) |
		((permissions >> 2) & S_IRWXG) |
		((permissions >> 4) & S_IRWXU) |
		((flags & ICBTAG_FLAG_SETUID) ? S_ISUID : 0) |
		((flags & ICBTAG_FLAG_SETGID) ? S_ISGID : 0) |
		((flags & ICBTAG_FLAG_STICKY) ? S_ISVTX : 0);

	return mode;
}