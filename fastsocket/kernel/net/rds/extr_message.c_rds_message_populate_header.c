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
typedef  int /*<<< orphan*/  u64 ;
struct rds_header {int /*<<< orphan*/ * h_exthdr; int /*<<< orphan*/  h_sequence; void* h_dport; void* h_sport; scalar_t__ h_flags; } ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_EXTHDR_NONE ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

void rds_message_populate_header(struct rds_header *hdr, __be16 sport,
				 __be16 dport, u64 seq)
{
	hdr->h_flags = 0;
	hdr->h_sport = sport;
	hdr->h_dport = dport;
	hdr->h_sequence = cpu_to_be64(seq);
	hdr->h_exthdr[0] = RDS_EXTHDR_NONE;
}