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
#define  IPPROTO_TCP 177 
#define  MPTCP_ALTERNATE_PORT 176 
#define  MPTCP_SERVICE_TYPE 175 
#define  PERSIST_TIMEOUT 174 
#define  SOL_SOCKET 173 
#define  SO_DEBUG 172 
#define  SO_DEFUNCTOK 171 
#define  SO_DELEGATED 170 
#define  SO_DELEGATED_UUID 169 
#define  SO_ERROR 168 
#define  SO_FLUSH 167 
#define  SO_ISDEFUNCT 166 
#define  SO_KEEPALIVE 165 
#define  SO_LABEL 164 
#define  SO_LINGER 163 
#define  SO_LINGER_SEC 162 
#define  SO_MARK_CELLFALLBACK 161 
#define  SO_NKE 160 
#define  SO_NOADDRERR 159 
#define  SO_NOAPNFALLBK 158 
#define  SO_NOSIGPIPE 157 
#define  SO_NOWAKEFROMSLEEP 156 
#define  SO_NREAD 155 
#define  SO_NWRITE 154 
#define  SO_OPPORTUNISTIC 153 
#define  SO_PEERLABEL 152 
#define  SO_PRIVILEGED_TRAFFIC_CLASS 151 
#define  SO_RANDOMPORT 150 
#define  SO_RCVBUF 149 
#define  SO_RCVLOWAT 148 
#define  SO_RCVTIMEO 147 
#define  SO_RECV_ANYIF 146 
#define  SO_RECV_TRAFFIC_CLASS 145 
#define  SO_RESTRICTIONS 144 
#define  SO_SNDBUF 143 
#define  SO_SNDLOWAT 142 
#define  SO_SNDTIMEO 141 
#define  SO_TRAFFIC_CLASS 140 
#define  SO_TRAFFIC_CLASS_DBG 139 
#define  SO_TYPE 138 
#define  SO_USELOOPBACK 137 
#define  TCP_ADAPTIVE_READ_TIMEOUT 136 
#define  TCP_ADAPTIVE_WRITE_TIMEOUT 135 
#define  TCP_CONNECTIONTIMEOUT 134 
#define  TCP_KEEPALIVE 133 
#define  TCP_KEEPCNT 132 
#define  TCP_KEEPINTVL 131 
#define  TCP_NODELAY 130 
#define  TCP_NOTSENT_LOWAT 129 
#define  TCP_RXT_CONNDROPTIME 128 

const char *
mptcp_sopt2str(int level, int optname)
{
	switch (level) {
	case SOL_SOCKET:
		switch (optname) {
		case SO_LINGER:
			return ("SO_LINGER");
		case SO_LINGER_SEC:
			return ("SO_LINGER_SEC");
		case SO_DEBUG:
			return ("SO_DEBUG");
		case SO_KEEPALIVE:
			return ("SO_KEEPALIVE");
		case SO_USELOOPBACK:
			return ("SO_USELOOPBACK");
		case SO_TYPE:
			return ("SO_TYPE");
		case SO_NREAD:
			return ("SO_NREAD");
		case SO_NWRITE:
			return ("SO_NWRITE");
		case SO_ERROR:
			return ("SO_ERROR");
		case SO_SNDBUF:
			return ("SO_SNDBUF");
		case SO_RCVBUF:
			return ("SO_RCVBUF");
		case SO_SNDLOWAT:
			return ("SO_SNDLOWAT");
		case SO_RCVLOWAT:
			return ("SO_RCVLOWAT");
		case SO_SNDTIMEO:
			return ("SO_SNDTIMEO");
		case SO_RCVTIMEO:
			return ("SO_RCVTIMEO");
		case SO_NKE:
			return ("SO_NKE");
		case SO_NOSIGPIPE:
			return ("SO_NOSIGPIPE");
		case SO_NOADDRERR:
			return ("SO_NOADDRERR");
		case SO_RESTRICTIONS:
			return ("SO_RESTRICTIONS");
		case SO_LABEL:
			return ("SO_LABEL");
		case SO_PEERLABEL:
			return ("SO_PEERLABEL");
		case SO_RANDOMPORT:
			return ("SO_RANDOMPORT");
		case SO_TRAFFIC_CLASS:
			return ("SO_TRAFFIC_CLASS");
		case SO_RECV_TRAFFIC_CLASS:
			return ("SO_RECV_TRAFFIC_CLASS");
		case SO_TRAFFIC_CLASS_DBG:
			return ("SO_TRAFFIC_CLASS_DBG");
		case SO_PRIVILEGED_TRAFFIC_CLASS:
			return ("SO_PRIVILEGED_TRAFFIC_CLASS");
		case SO_DEFUNCTOK:
			return ("SO_DEFUNCTOK");
		case SO_ISDEFUNCT:
			return ("SO_ISDEFUNCT");
		case SO_OPPORTUNISTIC:
			return ("SO_OPPORTUNISTIC");
		case SO_FLUSH:
			return ("SO_FLUSH");
		case SO_RECV_ANYIF:
			return ("SO_RECV_ANYIF");
		case SO_NOWAKEFROMSLEEP:
			return ("SO_NOWAKEFROMSLEEP");
		case SO_NOAPNFALLBK:
			return ("SO_NOAPNFALLBK");
		case SO_MARK_CELLFALLBACK:
			return ("SO_CELLFALLBACK");
		case SO_DELEGATED:
			return ("SO_DELEGATED");
		case SO_DELEGATED_UUID:
			return ("SO_DELEGATED_UUID");
#if NECP
		case SO_NECP_ATTRIBUTES:
			return ("SO_NECP_ATTRIBUTES");
		case SO_NECP_CLIENTUUID:
			return ("SO_NECP_CLIENTUUID");
#endif /* NECP */
		}

		break;
	case IPPROTO_TCP:
		switch (optname) {
		case TCP_NODELAY:
			return ("TCP_NODELAY");
		case TCP_KEEPALIVE:
			return ("TCP_KEEPALIVE");
		case TCP_KEEPINTVL:
			return ("TCP_KEEPINTVL");
		case TCP_KEEPCNT:
			return ("TCP_KEEPCNT");
		case TCP_CONNECTIONTIMEOUT:
			return ("TCP_CONNECTIONTIMEOUT");
		case TCP_RXT_CONNDROPTIME:
			return ("TCP_RXT_CONNDROPTIME");
		case PERSIST_TIMEOUT:
			return ("PERSIST_TIMEOUT");
		case TCP_NOTSENT_LOWAT:
			return ("NOTSENT_LOWAT");
		case TCP_ADAPTIVE_READ_TIMEOUT:
			return ("ADAPTIVE_READ_TIMEOUT");
		case TCP_ADAPTIVE_WRITE_TIMEOUT:
			return ("ADAPTIVE_WRITE_TIMEOUT");
		case MPTCP_SERVICE_TYPE:
			return ("MPTCP_SERVICE_TYPE");
		case MPTCP_ALTERNATE_PORT:
			return ("MPTCP_ALTERNATE_PORT");
		}

		break;
	}

	return ("unknown");
}