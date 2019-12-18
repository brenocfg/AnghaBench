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
struct nls_table {int dummy; } ;
struct cifs_ses {int /*<<< orphan*/ * domainName; int /*<<< orphan*/ * user_name; } ;
struct TYPE_2__ {char* release; } ;

/* Variables and functions */
 char* CIFS_NETWORK_OPSYS ; 
 int MAX_USERNAME_SIZE ; 
 TYPE_1__* init_utsname () ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ascii_ssetup_strings(char **pbcc_area, struct cifs_ses *ses,
				 const struct nls_table *nls_cp)
{
	char *bcc_ptr = *pbcc_area;

	/* copy user */
	/* BB what about null user mounts - check that we do this BB */
	/* copy user */
	if (ses->user_name != NULL)
		strncpy(bcc_ptr, ses->user_name, MAX_USERNAME_SIZE);
	/* else null user mount */

	bcc_ptr += strnlen(ses->user_name, MAX_USERNAME_SIZE);
	*bcc_ptr = 0;
	bcc_ptr++; /* account for null termination */

	/* copy domain */

	if (ses->domainName != NULL) {
		strncpy(bcc_ptr, ses->domainName, 256);
		bcc_ptr += strnlen(ses->domainName, 256);
	} /* else we will send a null domain name
	     so the server will default to its own domain */
	*bcc_ptr = 0;
	bcc_ptr++;

	/* BB check for overflow here */

	strcpy(bcc_ptr, "Linux version ");
	bcc_ptr += strlen("Linux version ");
	strcpy(bcc_ptr, init_utsname()->release);
	bcc_ptr += strlen(init_utsname()->release) + 1;

	strcpy(bcc_ptr, CIFS_NETWORK_OPSYS);
	bcc_ptr += strlen(CIFS_NETWORK_OPSYS) + 1;

	*pbcc_area = bcc_ptr;
}