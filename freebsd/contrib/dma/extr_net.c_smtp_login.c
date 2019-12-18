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
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int INSECURE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int SECURETRANS ; 
 int base64_encode (char*,int /*<<< orphan*/ ,char**) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  neterr ; 
 int read_remote (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_remote_command (int,char*,...) ; 
 int smtp_auth_md5 (int,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
smtp_login(int fd, char *login, char* password)
{
	char *temp;
	int len, res = 0;

	res = smtp_auth_md5(fd, login, password);
	if (res == 0) {
		return (0);
	} else if (res == -2) {
	/*
	 * If the return code is -2, then then the login attempt failed,
	 * do not try other login mechanisms
	 */
		return (1);
	}

	if ((config.features & INSECURE) != 0 ||
	    (config.features & SECURETRANS) != 0) {
		/* Send AUTH command according to RFC 2554 */
		send_remote_command(fd, "AUTH LOGIN");
		if (read_remote(fd, 0, NULL) != 3) {
			syslog(LOG_NOTICE, "remote delivery deferred:"
					" AUTH login not available: %s",
					neterr);
			return (1);
		}

		len = base64_encode(login, strlen(login), &temp);
		if (len < 0) {
encerr:
			syslog(LOG_ERR, "can not encode auth reply: %m");
			return (1);
		}

		send_remote_command(fd, "%s", temp);
		free(temp);
		res = read_remote(fd, 0, NULL);
		if (res != 3) {
			syslog(LOG_NOTICE, "remote delivery %s: AUTH login failed: %s",
			       res == 5 ? "failed" : "deferred", neterr);
			return (res == 5 ? -1 : 1);
		}

		len = base64_encode(password, strlen(password), &temp);
		if (len < 0)
			goto encerr;

		send_remote_command(fd, "%s", temp);
		free(temp);
		res = read_remote(fd, 0, NULL);
		if (res != 2) {
			syslog(LOG_NOTICE, "remote delivery %s: Authentication failed: %s",
					res == 5 ? "failed" : "deferred", neterr);
			return (res == 5 ? -1 : 1);
		}
	} else {
		syslog(LOG_WARNING, "non-encrypted SMTP login is disabled in config, so skipping it. ");
		return (1);
	}

	return (0);
}