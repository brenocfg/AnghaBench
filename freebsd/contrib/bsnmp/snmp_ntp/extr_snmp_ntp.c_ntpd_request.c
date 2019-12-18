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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;

/* Variables and functions */
 int DBG_DUMP_PKTS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 size_t NTPC_DMAX ; 
 int /*<<< orphan*/  NTPC_MAX ; 
 int NTPC_MODE ; 
 int NTPC_VERSION ; 
 int /*<<< orphan*/  dump_packet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntp_debug ; 
 int /*<<< orphan*/  ntpd_sock ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ seqno ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
ntpd_request(u_int op, u_int associd, const char *vars)
{
	u_char	*rpkt;
	u_char	*ptr;
	size_t	vlen;
	ssize_t	ret;

	if ((rpkt = malloc(NTPC_MAX)) == NULL) {
		syslog(LOG_ERR, "%m");
		return (-1);
	}
	memset(rpkt, 0, NTPC_MAX);

	ptr = rpkt;
	*ptr++ = (NTPC_VERSION << 3) | NTPC_MODE;
	*ptr++ = op;

	if (++seqno == 0)
		seqno++;
	*ptr++ = seqno >> 8;
	*ptr++ = seqno;

	/* skip status */
	ptr += 2;

	*ptr++ = associd >> 8;
	*ptr++ = associd;

	/* skip offset */
	ptr += 2;

	if (vars != NULL) {
		vlen = strlen(vars);
		if (vlen > NTPC_DMAX) {
			syslog(LOG_ERR, "NTP request too long (%zu)", vlen);
			free(rpkt);
			return (-1);
		}
		*ptr++ = vlen >> 8;
		*ptr++ = vlen;

		memcpy(ptr, vars, vlen);
		ptr += vlen;
	} else
		/* skip data length (is already zero) */
		ptr += 2;

	while ((ptr - rpkt) % 4 != 0)
		*ptr++ = 0;

	if (ntp_debug & DBG_DUMP_PKTS) {
		syslog(LOG_INFO, "sending %zd bytes", ptr - rpkt);
		dump_packet(rpkt, ptr - rpkt);
	}

	ret = send(ntpd_sock, rpkt, ptr - rpkt, 0);
	if (ret == -1) {
		syslog(LOG_ERR, "cannot send to ntpd: %m");
		free(rpkt);
		return (-1);
	}
	return (0);
}