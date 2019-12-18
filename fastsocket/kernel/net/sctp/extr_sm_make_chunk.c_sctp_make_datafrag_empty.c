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
struct sctp_sndrcvinfo {int sinfo_flags; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_stream; } ;
struct sctp_datahdr {void* ssn; int /*<<< orphan*/  ppid; void* stream; scalar_t__ tsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  sinfo; TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  dp ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_DATA ; 
 int /*<<< orphan*/  SCTP_DATA_UNORDERED ; 
 int SCTP_UNORDERED ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sctp_sndrcvinfo const*,int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_datahdr*) ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct sctp_chunk *sctp_make_datafrag_empty(struct sctp_association *asoc,
				       const struct sctp_sndrcvinfo *sinfo,
				       int data_len, __u8 flags, __u16 ssn)
{
	struct sctp_chunk *retval;
	struct sctp_datahdr dp;
	int chunk_len;

	/* We assign the TSN as LATE as possible, not here when
	 * creating the chunk.
	 */
	dp.tsn = 0;
	dp.stream = htons(sinfo->sinfo_stream);
	dp.ppid   = sinfo->sinfo_ppid;

	/* Set the flags for an unordered send.  */
	if (sinfo->sinfo_flags & SCTP_UNORDERED) {
		flags |= SCTP_DATA_UNORDERED;
		dp.ssn = 0;
	} else
		dp.ssn = htons(ssn);

	chunk_len = sizeof(dp) + data_len;
	retval = sctp_make_chunk(asoc, SCTP_CID_DATA, flags, chunk_len);
	if (!retval)
		goto nodata;

	retval->subh.data_hdr = sctp_addto_chunk(retval, sizeof(dp), &dp);
	memcpy(&retval->sinfo, sinfo, sizeof(struct sctp_sndrcvinfo));

nodata:
	return retval;
}