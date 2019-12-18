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
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  NFSD_AVAIL ; 
 int /*<<< orphan*/  NFSD_CLEAR ; 
 int /*<<< orphan*/  NFSD_SET ; 
 unsigned int NFSD_SUPPORTED_MINOR_VERSION ; 
 int /*<<< orphan*/  NFSD_TEST ; 
 int SIMPLE_TRANSACTION_LIMIT ; 
 scalar_t__ nfsd_minorversion (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_reset_versions () ; 
 scalar_t__ nfsd_serv ; 
 scalar_t__ nfsd_vers (int,int /*<<< orphan*/ ) ; 
 int qword_get (char**,char*,size_t) ; 
 int simple_strtol (char*,char**,int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static ssize_t __write_versions(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	char *vers, *minorp, sign;
	int len, num, remaining;
	unsigned minor;
	ssize_t tlen = 0;
	char *sep;

	if (size>0) {
		if (nfsd_serv)
			/* Cannot change versions without updating
			 * nfsd_serv->sv_xdrsize, and reallocing
			 * rq_argp and rq_resp
			 */
			return -EBUSY;
		if (buf[size-1] != '\n')
			return -EINVAL;
		buf[size-1] = 0;

		vers = mesg;
		len = qword_get(&mesg, vers, size);
		if (len <= 0) return -EINVAL;
		do {
			sign = *vers;
			if (sign == '+' || sign == '-')
				num = simple_strtol((vers+1), &minorp, 0);
			else
				num = simple_strtol(vers, &minorp, 0);
			if (*minorp == '.') {
				if (num < 4)
					return -EINVAL;
				minor = simple_strtoul(minorp+1, NULL, 0);
				if (minor == 0)
					return -EINVAL;
				if (nfsd_minorversion(minor, sign == '-' ?
						     NFSD_CLEAR : NFSD_SET) < 0)
					return -EINVAL;
				goto next;
			}
			switch(num) {
			case 2:
			case 3:
			case 4:
				nfsd_vers(num, sign == '-' ? NFSD_CLEAR : NFSD_SET);
				break;
			default:
				return -EINVAL;
			}
		next:
			vers += len + 1;
		} while ((len = qword_get(&mesg, vers, size)) > 0);
		/* If all get turned off, turn them back on, as
		 * having no versions is BAD
		 */
		nfsd_reset_versions();
	}

	/* Now write current state into reply buffer */
	len = 0;
	sep = "";
	remaining = SIMPLE_TRANSACTION_LIMIT;
	for (num=2 ; num <= 4 ; num++)
		if (nfsd_vers(num, NFSD_AVAIL)) {
			len = snprintf(buf, remaining, "%s%c%d", sep,
				       nfsd_vers(num, NFSD_TEST)?'+':'-',
				       num);
			sep = " ";

			if (len > remaining)
				break;
			remaining -= len;
			buf += len;
			tlen += len;
		}
	if (nfsd_vers(4, NFSD_AVAIL))
		for (minor = 1; minor <= NFSD_SUPPORTED_MINOR_VERSION;
		     minor++) {
			len = snprintf(buf, remaining, " %c4.%u",
					(nfsd_vers(4, NFSD_TEST) &&
					 nfsd_minorversion(minor, NFSD_TEST)) ?
						'+' : '-',
					minor);

			if (len > remaining)
				break;
			remaining -= len;
			buf += len;
			tlen += len;
		}

	len = snprintf(buf, remaining, "\n");
	if (len > remaining)
		return -EINVAL;
	return tlen + len;
}