#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * g_guid; } ;
typedef  TYPE_1__ guid_t ;

/* Variables and functions */
 int KAUTH_WKG_EVERYBODY ; 
 int KAUTH_WKG_GROUP ; 
 int KAUTH_WKG_NOBODY ; 
 int KAUTH_WKG_NOT ; 
 int KAUTH_WKG_OWNER ; 
 int OSSwapHostToBigInt32 (int) ; 
 scalar_t__ bcmp (void*,char*,int) ; 

int
kauth_wellknown_guid(guid_t *guid)
{
	static char	fingerprint[] = {0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef, 0xab, 0xcd, 0xef};
	uint32_t		code;
	/*
	 * All WKGs begin with the same 12 bytes.
	 */
	if (bcmp((void *)guid, fingerprint, 12) == 0) {
		/*
		 * The final 4 bytes are our code (in network byte order).
		 */
		code = OSSwapHostToBigInt32(*(uint32_t *)&guid->g_guid[12]);
		switch(code) {
		case 0x0000000c:
			return(KAUTH_WKG_EVERYBODY);
		case 0xfffffffe:
			return(KAUTH_WKG_NOBODY);
		case 0x0000000a:
			return(KAUTH_WKG_OWNER);
		case 0x00000010:
			return(KAUTH_WKG_GROUP);
		}
	}
	return(KAUTH_WKG_NOT);
}