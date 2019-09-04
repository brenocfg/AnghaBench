#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* kauth_filesec_t ;
typedef  TYPE_3__* kauth_acl_t ;
struct TYPE_8__ {scalar_t__ acl_entrycount; scalar_t__ acl_flags; TYPE_1__* acl_ace; } ;
struct TYPE_7__ {scalar_t__ fsec_magic; TYPE_3__ fsec_acl; } ;
struct TYPE_6__ {scalar_t__ ace_flags; scalar_t__ ace_rights; } ;

/* Variables and functions */
#define  KAUTH_ENDIAN_DISK 129 
#define  KAUTH_ENDIAN_HOST 128 
 scalar_t__ KAUTH_FILESEC_MAGIC ; 
 scalar_t__ KAUTH_FILESEC_NOACL ; 
 void* ntohl (scalar_t__) ; 

void
kauth_filesec_acl_setendian(int kendian, kauth_filesec_t fsec, kauth_acl_t acl)
{
 	uint32_t	compare_magic = KAUTH_FILESEC_MAGIC;
	uint32_t	invert_magic = ntohl(KAUTH_FILESEC_MAGIC);
	uint32_t	compare_acl_entrycount;
	uint32_t	i;

	if (compare_magic == invert_magic)
		return;

	/* If no ACL, use ACL interior to 'fsec' instead */
	if (acl == NULL)
		acl = &fsec->fsec_acl;

	compare_acl_entrycount = acl->acl_entrycount;

	/*
	 * Only convert what needs to be converted, and only if the arguments
	 * are valid.  The following switch and tests effectively reject
	 * conversions on invalid magic numbers as a desirable side effect.
	 */
 	switch(kendian) {
	case KAUTH_ENDIAN_HOST:		/* not in host, convert to host */
		if (fsec->fsec_magic != invert_magic)
			return;
		/* acl_entrycount is byteswapped */
		compare_acl_entrycount = ntohl(acl->acl_entrycount);
		break;
	case KAUTH_ENDIAN_DISK:		/* not in disk, convert to disk */
		if (fsec->fsec_magic != compare_magic)
			return;
		break;
	default:			/* bad argument */
		return;
	}
	
	/* We are go for conversion */
	fsec->fsec_magic = ntohl(fsec->fsec_magic);
	acl->acl_entrycount = ntohl(acl->acl_entrycount);
	if (compare_acl_entrycount != KAUTH_FILESEC_NOACL) {
		acl->acl_flags = ntohl(acl->acl_flags);

		/* swap ACE rights and flags */
		for (i = 0; i < compare_acl_entrycount; i++) {
			acl->acl_ace[i].ace_flags = ntohl(acl->acl_ace[i].ace_flags);
			acl->acl_ace[i].ace_rights = ntohl(acl->acl_ace[i].ace_rights);
		}
	}
 }