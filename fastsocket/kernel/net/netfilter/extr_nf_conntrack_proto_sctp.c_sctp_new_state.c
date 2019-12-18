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
typedef  enum sctp_conntrack { ____Placeholder_sctp_conntrack } sctp_conntrack ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
#define  SCTP_CID_ABORT 136 
#define  SCTP_CID_COOKIE_ACK 135 
#define  SCTP_CID_COOKIE_ECHO 134 
#define  SCTP_CID_ERROR 133 
#define  SCTP_CID_INIT 132 
#define  SCTP_CID_INIT_ACK 131 
#define  SCTP_CID_SHUTDOWN 130 
#define  SCTP_CID_SHUTDOWN_ACK 129 
#define  SCTP_CID_SHUTDOWN_COMPLETE 128 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/ * sctp_conntrack_names ; 
 size_t*** sctp_conntracks ; 

__attribute__((used)) static int sctp_new_state(enum ip_conntrack_dir dir,
			  enum sctp_conntrack cur_state,
			  int chunk_type)
{
	int i;

	pr_debug("Chunk type: %d\n", chunk_type);

	switch (chunk_type) {
	case SCTP_CID_INIT:
		pr_debug("SCTP_CID_INIT\n");
		i = 0;
		break;
	case SCTP_CID_INIT_ACK:
		pr_debug("SCTP_CID_INIT_ACK\n");
		i = 1;
		break;
	case SCTP_CID_ABORT:
		pr_debug("SCTP_CID_ABORT\n");
		i = 2;
		break;
	case SCTP_CID_SHUTDOWN:
		pr_debug("SCTP_CID_SHUTDOWN\n");
		i = 3;
		break;
	case SCTP_CID_SHUTDOWN_ACK:
		pr_debug("SCTP_CID_SHUTDOWN_ACK\n");
		i = 4;
		break;
	case SCTP_CID_ERROR:
		pr_debug("SCTP_CID_ERROR\n");
		i = 5;
		break;
	case SCTP_CID_COOKIE_ECHO:
		pr_debug("SCTP_CID_COOKIE_ECHO\n");
		i = 6;
		break;
	case SCTP_CID_COOKIE_ACK:
		pr_debug("SCTP_CID_COOKIE_ACK\n");
		i = 7;
		break;
	case SCTP_CID_SHUTDOWN_COMPLETE:
		pr_debug("SCTP_CID_SHUTDOWN_COMPLETE\n");
		i = 8;
		break;
	default:
		/* Other chunks like DATA, SACK, HEARTBEAT and
		its ACK do not cause a change in state */
		pr_debug("Unknown chunk type, Will stay in %s\n",
			 sctp_conntrack_names[cur_state]);
		return cur_state;
	}

	pr_debug("dir: %d   cur_state: %s  chunk_type: %d  new_state: %s\n",
		 dir, sctp_conntrack_names[cur_state], chunk_type,
		 sctp_conntrack_names[sctp_conntracks[dir][i][cur_state]]);

	return sctp_conntracks[dir][i][cur_state];
}