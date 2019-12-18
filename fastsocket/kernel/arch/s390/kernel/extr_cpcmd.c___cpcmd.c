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

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EBCASC (char*,int) ; 
 int /*<<< orphan*/  cpcmd_buf ; 
 int diag8_noresponse (int) ; 
 int diag8_response (int,char*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

int  __cpcmd(const char *cmd, char *response, int rlen, int *response_code)
{
	int cmdlen;
	int rc;
	int response_len;

	cmdlen = strlen(cmd);
	BUG_ON(cmdlen > 240);
	memcpy(cpcmd_buf, cmd, cmdlen);
	ASCEBC(cpcmd_buf, cmdlen);

	if (response) {
		memset(response, 0, rlen);
		response_len = rlen;
		rc = diag8_response(cmdlen, response, &rlen);
		EBCASC(response, response_len);
        } else {
		rc = diag8_noresponse(cmdlen);
        }
	if (response_code)
		*response_code = rc;
	return rlen;
}